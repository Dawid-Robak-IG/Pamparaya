//
// Created by dawid on 30.04.2023.
//

#include "Pamparaya.h"

Pamparaya::Pamparaya(int hp,int nr_of_actions,int board_height, int board_width, Weapon &w)
{
    this->board_height=board_height;
    this->board_width=board_width;
    weapon=&w;//aktualna bron ktora dzierzy bohater
    health=hp;
    this->nr_of_actions=nr_of_actions;
    current_nr_actions=nr_of_actions;
    sight=4;
//    row=board_height/2;
//    column=board_width/2;
    coords.x = board_width/2;
    coords.y  = board_height/2;
    lvl=1;
    exp=0;
    picked_rocks=0;
    rocksForMountain=5;
    appearance=STANDING;
    SetUseablePoints();
    SetSound();
}
void Pamparaya::SetUseablePoints()
{
    /*
     Dodaje do vetora useable_points wzgledne punkty (punkty graifcznego boarda) ktore
     to ustalaja ktore pola wzgledem bohatera moga zostac nacisniete by
     wykonac akcje (atak, postawienie gory)
     * */
    Point point={-1,0};
    useable_points.push_back(point);
    point={1,0};
    useable_points.push_back(point);
    point={0,1};
    useable_points.push_back(point);
    point={0,-1};
    useable_points.push_back(point);
}
void Pamparaya::SetSound()
{
    /*
     Ustala dzwiek chodzenia
     * */
    if(!buffer.loadFromFile("../Sounds/walking.ogg"))
    {
        std::cout<<"No sound walking"<<std::endl;
    }
    sound.setBuffer(buffer);
}
bool Pamparaya::does_attack(int row_attacked, int col_attacked)
{
    /*
    row_attacked oraz col_attaked sa wspolrzednymi graficznego pola (tego ktore sie wyswietla)
    funkcja zwroci prawde jesli suma sight i ktorejkolwiek z wielkosci wektora useable_points jest rowna podanym
     zaatakowanym wspolrzednym graficznym.
    w przeciwnym wypadku funckja zwroci false
    funckja zwroci false rowniez gdy bohater nie ma juz niewykorzystanych oraz akcje jego broni sa wykorzystane
     * */
    if(weapon->get_current_number_of_use()<1 or current_nr_actions<1)return false;
    for(int i=0;i<useable_points.size();i++)
    {
        if( sight+useable_points[i].y==row_attacked and sight+useable_points[i].x==col_attacked)
            return true;
    }
    return false;
}
bool Pamparaya::does_put_mountain(int row_attacked,int col_attacked)
{
    /*
    row_attacked oraz col_attaked sa wspolrzednymi graficznego pola (tego ktore sie wyswietla)
     funckja zwroci false gdy bohater nie ma juz niewykorzystanych akcji
     lub tez bohater nie ma wystarczajacej ilosci kamieni

     funkcja zwroci prawde jesli suma sight i ktorejkolwiek z wielkosci wektora useable_points jest rowna podanym
     zaatakowanym wspolrzednym graficznym.
     w przeciwnym wypadku funckja zwroci false
     * */
    if(current_nr_actions<1)return false;
    if(picked_rocks<rocksForMountain)return false;
    for(int i=0;i<useable_points.size();i++)
    {
        if( sight+useable_points[i].y==row_attacked and sight+useable_points[i].x==col_attacked)
            return true;
    }
    return false;
}

void Pamparaya::move(WHERE_TO_GO direction)
{
    /*
     Funckja zmieni wspolrzedne bohatera (o ile bohater ma niewykorzystane akcje)
     zaleznie od wybranego kierunku
     zmieni poze bohatera na stojaca
     nastepnie zmiejszy ilosc niewykorzystanych akcji
     * */
    if(nr_of_actions<1)return;

    if(direction==UP)coords.y--;
    else if(direction==DOWN)coords.y++;
    else if(direction==RIGHT)coords.x++;
    else coords.x--;//LEFT

    ResetAppearance(STANDING);
    current_nr_actions--;
}

void Pamparaya::SetAppearance(int attacking_row, int attacking_col)
{
    /*
        row_attacked oraz col_attaked sa wspolrzednymi graficznego pola (tego ktore sie wyswietla)
        funkcja ustala wyglad bohatera w zaleznosci od strony w ktora musi sie zwrocic bohater by wskazywac (reka, oczy)
        na dane pole
    * */
    if(attacking_col>sight and attacking_row==sight)appearance=RIGHT;
    else if(attacking_col<sight and attacking_row==sight)appearance=LEFT;
    else if(attacking_row<sight and attacking_col==sight)appearance=UP;
    else if(attacking_row>sight and attacking_col==sight)appearance=DOWN;
}

void Pamparaya::ResetAppearance(WHERE_TO_GO how_to_look)
{
    appearance=how_to_look;
}

void Pamparaya::end_of_turn()
{
    current_nr_actions=nr_of_actions;
}
void Pamparaya::ChangeWeapon(Weapon &w)
{
    appearance=STANDING;
    weapon=&w;
}
void Pamparaya::DidAction()
{
    current_nr_actions--;
}
void Pamparaya::be_attacked(int dmgToTake)
{
    health-=dmgToTake;
}
bool Pamparaya::does_lvlUp(int expToIncrease)
{
    /*
     * funkcja zwieksza ilosc exp bohatera
     * oraz sprawdza czy bohater osiagnal kolejny poziom
     * jesli tak to zwieksza poziom boatera oraz zwraca true
     * a jesli nie to nei zwieksza lvl bohatera i zwraca false
     * */
    exp+=expToIncrease;
    if(exp>=get_exp_tolvlup())
    {
        lvl++;
        return true;
    }
    return false;
}
void Pamparaya::apply_buff(Buff buff)
{
    nr_of_actions+=buff.actions_value;
}
void Pamparaya::picked_rock()
{
    picked_rocks++;
}
void Pamparaya::have_put_mountain()
{
    ResetAppearance(STANDING);
    current_nr_actions--;
    picked_rocks-=rocksForMountain;
}
void Pamparaya::play_my_sound()
{
    sound.play();
}

Weapon* Pamparaya::get_weapon()
{
    return weapon;
}

int Pamparaya::get_sight() const
{
    return sight;
}
int Pamparaya::get_row() const
{
    return coords.y;
}
int Pamparaya::get_col() const
{
    return coords.x;
}
int Pamparaya::get_nr_of_actions() const
{
    return nr_of_actions;
}

WEAPON Pamparaya::get_choosen_weapon()
{
    return weapon->get_kind();
}

WHERE_TO_GO Pamparaya::get_appearance()
{
    return appearance;
}

int Pamparaya::get_current_nr_actions() const
{
    return current_nr_actions;
}
int Pamparaya::get_health() const
{
    return health;
}
int Pamparaya::get_exp() const
{
    return exp;
}
int Pamparaya::get_lvl() const
{
    return lvl;
}
int Pamparaya::get_exp_tolvlup() const
{
    return 13*lvl;
}
Point Pamparaya::get_position() const
{
    return coords;
}
int Pamparaya::get_picked_rocks() const
{
    return picked_rocks;
}
int Pamparaya::get_rocks_for_mountain() const
{
    return rocksForMountain;
}
std::vector<Point> Pamparaya::get_useablePoints() const
{
    return useable_points;
}