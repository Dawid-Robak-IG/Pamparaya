//
// Created by dawid on 29.04.2023.
//

#include "Board.h"
#include <chrono>
#include <thread>

Board::Board(int height,int width,int start_nr_rocks)
{
    /*
     height - ilosc wierszy w planszy
     width - ilosc kolumn w planszy\
     start_nr_rocks - ilosc kamieni do rozmieszczenia na poczatku gry
     * */
    if(height<3)height=3; //by plansza nie byla za mala
    if(width<3)width=3;

    this->height=height;
    this->width=width;
    possible_nr_rocks=height*width; //mozemy poczatkowo umiescic kamien na kazdym polu planszy
    totalValue=2;
    rocks_per_turn=2;

    //____________________________________________________________
    //zapelniamy tablice niezajetymi polami (gola trawa)
    std::vector<Object> board_help;
    Object object(GRASS);
    object.no_longer_occupied();
    for(int column=0;column<width;column++)
            board_help.push_back(object);
    for(int row=0;row<height;row++)
        board.push_back(board_help);
    //____________________________________________________________
    //umieszczamy kamienie
    int x,y,i=0;
    while(i < start_nr_rocks and i<possible_nr_rocks)
    {
        x=rand()%width;
        y=rand()%height;
        board[y][x].SetKind(ROCK);
        i++;
        possible_nr_rocks--;//umiescilismy kamien a wiec ilosc kamieni ktore mozemy potencjalnie umiescic
                            //zmiejsza sie
    }
    //cout_occupidity();
    //____________________________________________________________
    //wrzucaneie na plansze nowych przeciwnikow
    i=0;
    int nr_start_enemies=4;
    while(i<nr_start_enemies)
    {
        set_random_on_edges(x,y);//ustawiamy losowe wspolzedne na krancach planszy
        if(!board[y][x].get_occupied()) //pole nie moze byc zajete by stworzayc tam przeciwnika
        {
//            GreenSlime gslime(x, y,height,width,0);
            std::unique_ptr<Enemy> green_slime(new GreenSlime(x, y,height,width,0));
            enemies.push_back(std::move(green_slime));
            board[y][x].put_sth();
            i++;
        }
    }
}
bool Board::is_on_board(Point point)
{
    /*
     point to wspolrzedne na planszy
     zwraca prawde jedli podane wspolrzedne znajduja sie wewnatrz planszy
     w przeciwnym wypadku zwraca falsz
     **/
    if(point.y<0)return false;
    if(point.y>=height)return false;
    if(point.x<0) return false;
    if(point.x>=width)return false;

    return true;
}

void Board::deal_dmg(int dmg_to_apply,std::vector<Point>area_toDealDmg, int &expToGive)
{
    /*
     Funkcja ta ma na celu zadanie okreslonych obrazen przeciwnikom ktorzy znajduja sie na podanych polach,
     oraz zabicie tych ktorzy maja zycie mniejsze lub rowne zadanym obrazenia
     dmg_to_apply okresla ilosc obrazen ktore chcemy zadac przeciwnikowi
     are_toDealDmg - okresla wszystkie wspolrzedne na ktore chcemy zadac oobrazenia (przeciwnikom ktorzy sie tam
     znajduja)
     expToGive - (przez referencje) okresla calkowita warotsc przeciwnikow ktorzy zostali zabici
     * */
    for(int i=0;i<area_toDealDmg.size();i++)
    {
        //std::cout<<area_toDealDmg.size()<<std::endl;
        for(int k=0;k<enemies.size();k++)
        {
//            std::cout<<enemies[k].get_position().x<<" "<<enemies[k].get_position().y<<std::endl;
//            std::cout<<area_toDealDmg[i].x<<" "<<area_toDealDmg[i].y<<std::endl;
//            std::cout<<"_____"<<std::endl;
            if(enemies[k]->get_position()==area_toDealDmg[i])
            {
                enemies[k]->be_attacked(dmg_to_apply);
                if(enemies[k]->get_hp()<=0)
                {
                    expToGive+=enemies[k]->get_value();
                    board[area_toDealDmg[i].y][area_toDealDmg[i].x].no_longer_occupied();
                    enemies.erase(enemies.begin()+k);
//                    std::cout<<"area (x,y): "<<area_toDealDmg[i].x<<" "<<area_toDealDmg[i].y<<std::endl;
//                    std::cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<<std::endl;
                }
            }
        }
    }
}

void Board::end_of_turn(Point HeroLocation, int &DmgToGive, int nr_turns)
{
    /*
     * HeroLocation - to nic innego jak wspolrzedne bohatera na planszy
     * DmgToGive to obrazenia ktore maja byc zadane bohaterowi
     * nr_turns - to numer tury, jest to potrzebne przy dodawaniu nowych przecinikow
     Funckja po kolei wykonuje operacje:
     -przemieszczenia przeciwnikow
     -zadania obrazen bohaterowi
     -postawienia nowych kamieni
     -dodania nowych przeciwnikow
     * */
    int x,y;
    std::vector<attackingInfo> attacking_info;

    move_enemies();

    add_new_enemies(nr_turns);
    DmgToGive = get_dmg_to_hurt_hero(HeroLocation);
    put_new_rocks();
}
void Board::move_enemies()
{
    /*
     Funkcja przemieszcza przeciwnikow
     Dla kazdego przeciwnika losuje sie jego nowe polozenie wedlug tego gdzie dany przeciwnik moze pojsc
     Moze sie zdarzyc iz przeciwnik bedzie chcial pojsc na juz zajete pole
     Wtedy to przeciwnik nigdzie sie nie ruszy
     * */
    for(int k=0;k<enemies.size();k++)
    {
        Point pom_pos=enemies[k]->get_rand_whereCanGo()+enemies[k]->get_position();
        if( is_on_board(pom_pos) and !board[pom_pos.y][pom_pos.x].get_occupied())
            //skoro tam gdize przeciwnik sie przemiszcza istnieje plansza oraz nic tam nie ma mozemy go tam umiescic
        {
            //przekazujemy informacje o tym ze nikogo nie ma na pierwotnej pozycji
            board[enemies[k]->get_position().y][enemies[k]->get_position().x].no_longer_occupied();
            //dajemu mu nowo pozycje
            enemies[k]->SetPosition(pom_pos);
            //infomujemy iz teraz na tej pozycji cos sie znajduje
            board[pom_pos.y][pom_pos.x].put_sth();
        }
    }
}
int Board::get_dmg_to_hurt_hero(Point HeroLocation)
{
    /*
     zwraca obrazenia ktory przeciwnicy moga aktualnie zadac bohaterowi,
     HeroLocation to wspolrzedne bohatera na planszy
     ta funkcja rowniez odgrywa dziwek ataku (wywoluje ten dzwiek)
     * */
    int DmgToGive=0;
    for(int k=0;k<enemies.size();k++)
    {
        for(int i=0;i<enemies[k]->get_AttackArea().size();i++)
        {
            if(enemies[k]->get_whereCouldAttack(i)==HeroLocation)
            {
                DmgToGive+=enemies[k]->get_dmg();
                //play_hit_sound(enemies[k]->get_type());
                enemies[k]->play_my_sound();
//                std::cout<<"atak"<<std::endl;
            }
        }
    }
//    std::cout<<"____________"<<std::endl;
    return DmgToGive;
}
void Board::put_new_rocks()
{
    /*
     kladzie kamienie na planszy,
     ilosc polozonych kamieni jest zalezna od zmiennen rocks_per_turn oraz ile
     jeszcze kamieni moze zostac polozonyhc na planszy (nie mozemy polozyc kamieni na kamieniach
     oraz na gorach),

     Funkcja zmienie wartosc zmiennej possible_nr_rocks (skoro polozylismy kamien to ilosc kamieni ktore mozemy jeszcze
     polozyc zmniejsza sie)
     Funkcja zmienia wartosci pol (nadaje im wartosci odpowiedne dla kamieni) -> uzywa do tego funkcji SetKind
     * */
    int i=0;
    int x,y;
    while(i<rocks_per_turn and i<possible_nr_rocks)
    {
        x=rand()%width;
        y=rand()%height;
        if(board[y][x].get_destroyable() and board[y][x].get_kind()!=ROCK)
        {
            board[y][x].SetKind(ROCK);
            possible_nr_rocks--;
            i++;
        }
    }
}
void Board::add_new_enemies(int nr_turns)
{
    /*
     Dodaje nowych przeciwnikow do vectora enemies,
     Ilosc przeciwnikow jest zalezna od totalValue ktora okresla calkowita maksymalna wartosc
     dodanych przeciwnikow, funkcja rowniez nie doda nowego przecinika jesli beda zajete wszystkie
     graniczne pola,
     Pole na ktorym pojawia sie przeciwnik staje sie zajete
     Funckja zwieksza rowniez total value az ta osiagnie ustalona tutaj wartosc
     * */
    int i=0;
    int x,y;
    while(i<totalValue and anyEdgePointFree())
    {
        set_random_on_edges(x,y);
        if(!board[y][x].get_occupied())
        {
            if(rand()%2==0)
            {
//                GreenSlime gSlime(x,y,height,width,nr_turns);
                std::unique_ptr<Enemy> green_slime(new GreenSlime(x,y,height,width,nr_turns));
                i+=green_slime->get_value();
                enemies.push_back(std::move(green_slime));
            }
            else
            {
//                PurpleSlime pSlime(x,y,height,width,nr_turns);
                std::unique_ptr<Enemy> purple_slime(new PurpleSlime(x,y,height,width,nr_turns));
                i+=purple_slime->get_value();
                enemies.push_back(std::move(purple_slime));
            }
            board[y][x].put_sth();
        }
    }
    if(totalValue<5)totalValue++;
}

void Board::set_random_on_edges(int &x, int &y)
{
    /*
     Funkcja nadaje zmiennym x i y losowe wartosci na krancach planszy
     * */
    int k=rand()%4;
    if(k==0)
    {
        x=0;
        y=rand()%height;
    }
    else if(k==1)
    {
        x=width-1;
        y=rand()%height;
    }
    else if(k==2)
    {
        y=0;
        x=rand()%width;
    }
    else
    {
        y=height-1;
        x=rand()%width;
    }
}

bool Board::anyEdgePointFree()
{
    /*
     Funkcja zwaca prawde jesli chociaz jedno pole graniczne nie jest zajete
     w przeciwnym wypadku zwraca false
     * */
    int x=0,y=0;
    while(y<height)
    {
        if(!board[y][0].get_occupied())return true;
        if(!board[y][width-1].get_occupied())return true;
        y++;
    }
    x=1;//pierwszy juz sprawdzony
    while(x<width-1) //ostatni rowniez sprawdzony
    {
        if(!board[0][x].get_occupied())return true;
        if(!board[height-1][x].get_occupied())return true;
        x++;
    }
    return false;
}

void Board::occupy(int x, int y)
{
    /*
     jesli podane wspolzedne sa w zakresie wspolrzednych planszy
     to wtedy tym wpolrzednym nadaje sie wartosc zajeta (occupied)
     * */
    if(!is_on_board({x,y})) return;
    board[y][x].put_sth();
}
void Board::occupy(Point point)
{
    /*
     jesli podane wspolzedne sa w zakresie wspolrzednych planszy
     to wtedy tym wpolrzednym nadaje sie wartosc zajeta (occupied)
     * */
    if(!is_on_board(point)) return;
    board[point.y][point.x].put_sth();
}
void Board::un_occupy(int x, int y)
{
    /*
     jesli podane wspolzedne sa w zakresie wspolrzednych planszy
     to wtedy tym wpolrzednym nadaje sie wartosc niezajeta (unoccupied)
     * */
    if(!is_on_board({x,y})) return;
    board[y][x].no_longer_occupied();
}
void Board::un_occupy(Point point)
{
    /*
     jesli podane wspolzedne sa w zakresie wspolrzednych planszy
     to wtedy tym wpolrzednym nadaje sie wartosc niezajeta (unoccupied)
     * */
    if(!is_on_board(point)) return;
    board[point.y][point.x].no_longer_occupied();
}

void Board::Set_Enemies_attacks(Point HeroLocation)
{
    /*
     czysci vector ktory zawiera zmienne ktore zawieraja:
     -typ przeciwnika
     -lokacje przeciwnika (nie aktualna, ta ktora byla aktualna w momencie wywolania tej funkcji)
     nadaje vectorowi atakow przeciwnikow nowe wartosci (typ przeciwnika ktory moze zadac obrazenia przeciwnikowi
     oraz jego pozycja),

     HeroLocation - jest wspolrzednymi bohatera na planszy
     * */
    enemies_attacks.clear();
    for(int k=0;k<enemies.size();k++)
    {
        for(int i=0;i<enemies[k]->get_AttackArea().size();i++)
        {
            if(enemies[k]->get_whereCouldAttack(i)==HeroLocation)
                enemies_attacks.push_back({enemies[k]->get_type(), enemies[k]->get_position()});
        }
    }
}
void Board::Set_To_Kind(Point coordinates, KINDS kind)
{
    /*
     jesli tylko dane wspolrzedne znajduja sie na mapie ustwia wortosci pola
     o tych wspolrzednych na odpowiadajace jej wartosci (nie zmienia tylko typu!!!)
     * */
    if(!is_on_board(coordinates))return;
    board[coordinates.y][coordinates.x].SetKind(kind);
}
void Board::Rock_Has_Been_Grabbed()
{
    possible_nr_rocks++;
}
bool Board::Are_Edges_Mountains()
{
    /*
     Funckja ma za zadanie sprawdzic czy na wszystkich krancowych polach sa gory
     */
    for(int y=0;y<height;y++)
    {
        if(board[y][0].get_destroyable())return false;
        if(board[y][width-1].get_destroyable())return false;
    }
    for(int x=1;x<width-1;x++)
    {
        if(board[0][x].get_destroyable())return false;
        if(board[height-1][x].get_destroyable())return false;
    }
    return true;
}
bool Board::Put_Erase_Mountain(Point point)
{
    /*
     Funkcja zwraca true jesli udalo sie polozyc/usunac gore
     Funkcja zwraca flase jesli pole bylo zajete nie gora

     Funckja kladzie i usuwa gore (jesli juz byla tam gora to usuwa)
     Funckja rowniez zmiejsza/zwieksza ilosc mozliwych kamieni do polozenia (nie mozna klasc kamienia
     na gorze)
     * */

    //jesli pole jest zajete (ale nie gora0 znaczy ze nie mozemy tam postawic gory
    if(board[point.y][point.x].get_occupied() and board[point.y][point.x].get_kind()!=MOUNTAIN)return false;

    if(board[point.y][point.x].get_kind()!=MOUNTAIN)
    {
        board[point.y][point.x].SetKind(MOUNTAIN);
        possible_nr_rocks--;
    }
    else //juz jest tam gora, chcemy ja usunac
    {
        board[point.y][point.x].SetKind(GRASS);
        board[point.y][point.x].no_longer_occupied();
        possible_nr_rocks++;
    }
    return true;
}

int Board::get_height() const
{
    return height;
}
int Board::get_width() const
{
    return width;
}
Object Board::get_Object(int row, int col) const
{
    return board[row][col];
}
Object Board::get_Object(Point coordinates) const
{
    return board[coordinates.y][coordinates.x];
}

int Board::get_nr_of_enemies() const
{
    return enemies.size();
}

Point Board::get_enemy_position(int which)
{
    return enemies[which]->get_position();
}

bool Board::isFieldOccupied(int x, int y)
{
    if(!is_on_board({x,y}))return true;
    return board[y][x].get_occupied();
}
bool Board::isFieldOccupied(Point point)
{
    if(!is_on_board(point))return true;
    return board[point.y][point.x].get_occupied();
}

ENEMIES_TYPIES Board::get_type(int which)
{
    return enemies[which]->get_type();
}
std::vector<attackingInfo> Board::get_enemies_attacks() const
{
    return enemies_attacks;
}
int Board::get_enemy_hp(int which)
{
    return enemies[which]->get_hp();
}
KINDS Board::get_kind(Point coordinates)
{
    return board[coordinates.y][coordinates.x].get_kind();
}

void Board::cout_occupidity()
{
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            std::cout<<"(x,y): "<<x<<","<<y<<"->";
            if(board[y][x].get_occupied())std::cout<<"occupied"<<std::endl;
            else std::cout<<"free"<<std::endl;
        }
    }
    std::cout<<"________________________"<<std::endl;
}

void Board::cout_enemies_pos()
{
    for(int i=0;i<enemies.size();i++)
    {
        std::cout<<i<<"(x,y). "<<enemies[i]->get_position().x<<" "<<enemies[i]->get_position().y<<std::endl;
    }
    std::cout<<"_______________________________"<<std::endl;
}