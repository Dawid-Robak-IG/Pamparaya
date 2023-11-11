//
// Created by dawid on 30.04.2023.
//

#include "SFMLController.h"

SFMLController::SFMLController(Board &b, Pamparaya &Pam,SFMLView &v, Weapon &s, Weapon &b_, Weapon &a):
board(b),pamparaya(Pam), view(v), sword(s), bow(b_),axe(a)
{
    turns=1;
}


void SFMLController::play(sf::Event &event)
{
    /*
     * Funkcja obsluguje ruchy bohatera zwiazane z naciskaniem klawiszy na klawiaturze i wywoluje do tego odpowiednie
     * funkcje:
     * -ruch
     * -zmiana broni
     * -pominiecie tury (space)
     *
     * Funckcja sprawdza rowniez czy bohater znajduje sie na kamieniu a jesli tak to
     * informuje bohatera ze ten zebral kamien
     * ustawia rodzaj pola na odpowiadajacy trawie (ale dodatkowo kaze planszy nadac temu polu wartosc
     * zajetej gdyz znajduje sie na nim bohater),
     * oraz informuje boarda ze jeden z kamieni zostal zebrany
     *
     * Funkcja wywoluje funkcje ktora zajmuje sie podnoszeniem kamieni przez bohatera
     * Funckja rowniez sprawdza czy nie nastapil koniec tury, a jesli nastapil wywoluje funkcje konca tury
     * */

    //movement
    if((event.key.code==sf::Keyboard::W or event.key.code==sf::Keyboard::Up) and can_hero_move(UP))
        try_move_hero({0,-1},UP);
    else if((event.key.code==sf::Keyboard::S or event.key.code==sf::Keyboard::Down)and can_hero_move(DOWN))
        try_move_hero({0,1},DOWN);
    else if((event.key.code==sf::Keyboard::D or event.key.code==sf::Keyboard::Right)and can_hero_move(RIGHT))
        try_move_hero({1,0},RIGHT);
    else if((event.key.code==sf::Keyboard::A or event.key.code==sf::Keyboard::Left) and can_hero_move(LEFT))
        try_move_hero({-1,0},LEFT);
    else if(event.key.code==sf::Keyboard::Num1)
        pamparaya.ChangeWeapon(sword);
    else if(event.key.code==sf::Keyboard::Num2)
        pamparaya.ChangeWeapon(bow);
    else if(event.key.code==sf::Keyboard::Num3)
        pamparaya.ChangeWeapon(axe);
    else if(event.key.code==sf::Keyboard::Space)
        end_of_turn();
//    else if(event.key.code==sf::Keyboard::M)//debug
//        board.cout_occupidity();
//    else if(event.key.code==sf::Keyboard::N)//debug
//        board.cout_enemies_pos();

    picking_rock();

    if(pamparaya.get_current_nr_actions()<1)
        end_of_turn();
}
void SFMLController::try_move_hero(Point pos_modifier,WHERE_TO_GO direction)
{
    /*
     * Funckja ma za zadanie sprawdzic czy pole na ktore chce przemiescic sie bohater jest wolne
     * oraz czy bohater posiada akcje by wykonac ten ruch
     * jesli te warunki sa spelnione funckja kaze bohaterowi sie przemiescic o wybrany kierunek
     * oraz informuje boarda iz dawne pole na ktorym byl bohater teraz jest puste (bohater sie przeniosl)
     * oraz infromuje boarda ktore pole teraz jest zajete (tam gdzie sie przeniosl bohater)
     * oraz odgrywa dzwiek bohatera (chodzenia)
     *
     * pos_modifier_x /y -> okreslaja zmiane w rzeczywistych wspolrzednych bohatera na boardzie
     * direction -> orkresla w ktorym kierunku ma sie przemiescic bohater
     * */
    if(!board.isFieldOccupied(pamparaya.get_position()+pos_modifier)
       and pamparaya.get_current_nr_actions()>0)
    {
        board.un_occupy(pamparaya.get_position());
        pamparaya.move(direction);
        pamparaya.play_my_sound();
        board.occupy(pamparaya.get_position());
//        std::cout<<"hero (x,y): "<<pamparaya.get_col()<<" "<<pamparaya.get_row()<<std::endl;
//        std::cout<<"board (x,y): "<<board.isFieldOccupied(pamparaya.get_col(),pamparaya.get_row())<<std::endl;
    }
}

void SFMLController::hero_attack(sf::RenderWindow &win, sf::Event event)
{
    /*
     * Jesli bohater ma niewykorzystana akcje oraz moze wykonac atak na dane pole gdzie znajduje sie mysz
     * wtedy ta funkcja wykonuje atak:
     * 1. Ustawia odpowiednio wyglad bohatera
     * 2. informuje boarda na jakie wspolrzedne zostal przyprowadzony atak oraz o jaka wartosc
     * 3. Zmniejsza ilosc niewykorzystanych akcji bohatera i broni (ktorra wykonano akcje)
     * 4. Zagra dzwiek broni ktorej uzyto
     * 5. Zwieksza doswiadczenie bohatera o wartosc zabitych wrogow, oraz jesli bohater osiagnal kolejny
     *    poziom wywoluje funkcje wyboru ulepszenia
     *
     * Funkcja wywoluje funkcje ktora zajmuje sie podnoszeniem kamieni przez bohatera
     * Funckja rowniez sprawdza czy nie nastapil koniec tury, a jesli nastapil wywoluje funkcje konca tury
     * */
    if(pamparaya.get_current_nr_actions()<1)
        return;

    int row=event.mouseButton.y/view.get_side_value()  ; //graifczne
    int column=event.mouseButton.x/view.get_side_value() ; //graficzne
    int expToGive=0;

    if(pamparaya.does_attack(row,column))
    {
        pamparaya.SetAppearance(row,column);
        board.deal_dmg(pamparaya.get_weapon()->get_dmg(),
                       pamparaya.get_weapon()->get_DealingDmgArea(
                               view.GraphicColumn_to_on_board(column),
                               view.GraphicRow_to_on_board(row),pamparaya.get_appearance()),
                               expToGive);
        pamparaya.get_weapon()->DecreaseCurrentUses();
        pamparaya.DidAction();
        pamparaya.get_weapon()->play_my_sound();

        if(pamparaya.does_lvlUp(expToGive))
        {
            choose_buf(win);
        }
//        board.cout_occupidity();//debug
//        board.cout_enemies_pos();
    }

    picking_rock();

    if(pamparaya.get_current_nr_actions()<1)
        end_of_turn();

}
void SFMLController::choose_buf(sf::RenderWindow &win)
{
    /*
     * Funkcja ma za zadanie pobranie losowych ulepszen broni a nastepnie wywolanie ekranu
     * wyboru ulepszenia z wybranymi ulepszeniami (ekran wyswietla sie do momentu wybrania ulepszenia),
     * */
    Buff swordBuff=sword.get_randBuff();
    Buff axeBuff=axe.get_randBuff();
    Buff bowBuff=bow.get_randBuff();
    bool isBuffChosen=false;

    while (win.isOpen())
    {
        win.clear();
        view.draw_choosingBuff(win, swordBuff,axeBuff,bowBuff);
        win.display();
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            else if(event.mouseButton.button == sf::Mouse::Left and event.type==sf::Event::MouseButtonPressed)
                isBuffChosen = choosingBuff(event,swordBuff,axeBuff,bowBuff);
        }
        if(isBuffChosen)
            break;
    }
}
void SFMLController::put_mountain(sf::Event &event)
{
    /*
     * Funkcja ma za zadanie postawic (lub tez usunac) gore na boardzie za pomoca przeksztalcenia wspolrzednych myszy na
     * rzeczywiste wsporzedne na boardzie
     *
     * Jesli bohater poinformuje iz moze postwic gore na wybranych wsporzednych to wstedy funkcja wywoluje funkcje
     * boarda, ktora ma za zadanie postwic/usunac gore oraz zwrocic informacje o sukcesje/porazce akcji
     * Jesli udalo sie usunac/postawic gore to wtedy funkcja (board juz poinformowal nas o sukcesie akcji) informuje
     * bohatera iz postawil/usunal gore
     *
     * Funkcja wywoluje funkcje ktora zajmuje sie podnoszeniem kamieni przez bohatera
     * Funckja rowniez sprawdza czy nie nastapil koniec tury, a jesli nastapil wywoluje funkcje konca tury
     * */
    int row=event.mouseButton.y/view.get_side_value()  ; //graifczne
    int column=event.mouseButton.x/view.get_side_value() ; //graficzne
    int trueRow=view.GraphicRow_to_on_board(row);
    int trueCol=view.GraphicColumn_to_on_board(column);

    //nie mozna polozyc gory na zajetym polu
    // mozna postawic gore na gorze
    if(pamparaya.does_put_mountain(row,column))
    {
        if(board.Put_Erase_Mountain({trueCol,trueRow}) )
        {
            pamparaya.have_put_mountain();
        }
    }

    picking_rock();
    if(pamparaya.get_current_nr_actions()<1)
        end_of_turn();
}


bool SFMLController::can_hero_move(WHERE_TO_GO direction)
{
    /*
     * direction -> kierunek w ktorym teoretycznie mialby sie udac bohater
     * jesli pole jest niezajete (pola poza plansza sa zajete)
     * to zwraca true
     * w przeciwnym wypadku false
     * jesli funkcja nie rozpozna kierunku to rowniez zwroci false
     * */
    if(direction==UP)
    {
        if(!board.isFieldOccupied(pamparaya.get_col(),pamparaya.get_row()-1))
            return true;
    }
    else if(direction==DOWN)
    {
        if(!board.isFieldOccupied(pamparaya.get_col(),pamparaya.get_row()+1))
            return true;
    }
    else if(direction==RIGHT)
    {
        if(!board.isFieldOccupied(pamparaya.get_col()+1,pamparaya.get_row()))
            return true;
    }
    else if(direction==LEFT)
    {
        if(!board.isFieldOccupied(pamparaya.get_col()-1,pamparaya.get_row()))
            return true;
    }
    return false;
}

void SFMLController::end_of_turn()
{
    /*
     * funkcja wywoluje funkcje end_of_turn dla wszystkich funkcji
     * kaze boardowi ustanowic vector atakow przeciwnikow (sluzy do pozniejszego wyswietlania atakow przeciwnikow)
     * zwieksza ilosc tur
     * imformuje bohatera o wartosci obrazen jakimi zostal zaatakowany
     * */
    int DmgToGive=0;
    pamparaya.end_of_turn();
    sword.end_of_turn();
    bow.end_of_turn();
    axe.end_of_turn();
    board.end_of_turn(pamparaya.get_position(),DmgToGive,turns);
    board.Set_Enemies_attacks(pamparaya.get_position()); //sluzy do wyswietlania atakow

    pamparaya.be_attacked(DmgToGive);
    turns++;
}

bool SFMLController::choosingBuff(sf::Event &event,const Buff& swordBuff, const Buff& axeBuff, const Buff& bowBuff)
{
    /*
     * Funkcja sprawdza czy myszka wybrano jakies ulepszenie i jesli wybrano zwraca true
     * w przeciwnym wypadku zwraca false
     *
     * Funkcja rowniez aplikuje ulepszenia (jesli jakies wybrano),
     * jesli wybrano bonus dla miecza wywoluje funkcje apply buff dla miecza
     * i analogicznie dla kazdej broni,
     * wywoluje sie rowniez apply buff dla bohatera (zmiana liczby akcji na ture)
     * */

    //sword
    if(event.mouseButton.x<view.get_swordRec_Info().posX+view.get_swordRec_Info().width
                                and event.mouseButton.x>view.get_swordRec_Info().posX)
        if(event.mouseButton.y<view.get_swordRec_Info().posY+view.get_swordRec_Info().height
                            and event.mouseButton.y>view.get_swordRec_Info().posY)
        {
            sword.apply_buff(swordBuff);
            pamparaya.apply_buff(swordBuff);
            return true;
        }
    //axe
    if(event.mouseButton.x<view.get_axeRec_Info().posX+view.get_axeRec_Info().width
                        and event.mouseButton.x>view.get_axeRec_Info().posX)
        if(event.mouseButton.y<view.get_axeRec_Info().posY+view.get_axeRec_Info().height
           and event.mouseButton.y>view.get_axeRec_Info().posY)
        {
            axe.apply_buff(axeBuff);
            pamparaya.apply_buff(axeBuff);
            return true;
        }
    //bow
    if(event.mouseButton.x<view.get_bowRec_Info().posX+view.get_bowRec_Info().width
                    and event.mouseButton.x>view.get_bowRec_Info().posX)
        if(event.mouseButton.y<view.get_bowRec_Info().posY+view.get_bowRec_Info().height
           and event.mouseButton.y>view.get_bowRec_Info().posY)
        {
            bow.apply_buff(bowBuff);
            pamparaya.apply_buff(bowBuff);
            return true;
        }
    return false;
}
void SFMLController::picking_rock()
{
    /*
        Funckcja sprawdza rowniez czy bohater znajduje sie na kamieniu a jesli tak to
        * informuje bohatera ze ten zebral kamien
        * ustawia rodzaj pola na odpowiadajacy trawie (ale dodatkowo kaze planszy nadac temu polu wartosc
        * zajetej gdyz znajduje sie na nim bohater),
        * oraz informuje boarda ze jeden z kamieni zostal zebrany
     * */
    if(board.get_kind(pamparaya.get_position())==ROCK)
    {
        pamparaya.picked_rock();
        board.Set_To_Kind(pamparaya.get_position(),GRASS);
        board.Rock_Has_Been_Grabbed();
    }
}

int SFMLController::get_turns() const
{
    return turns;
}