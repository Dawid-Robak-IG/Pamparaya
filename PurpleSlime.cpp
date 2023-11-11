//
// Created by c on 5/24/23.
//

#include "PurpleSlime.h"

PurpleSlime::PurpleSlime(int x, int y,int boardHeight,int boardWidth, int nr_turns):
                            Enemy(x,y,boardHeight,boardWidth)
{
    hp=10+nr_turns/8;
    value=2;
    dmg=3;
    type=PURPLE_SLIME;
    Set_WhereCanGo();
    Set_AttackArea();

    SetSound();
    amount++;
}
void PurpleSlime::Set_WhereCanGo()
{
    /*
     Funkcja ustala wszystkie mozliwe zmiany polozenia przeciwnika jakie moze wykonac przeciwnik
     * */
    whereCanGo.push_back({1,0});
    whereCanGo.push_back({-1,0});
    whereCanGo.push_back({0,1});
    whereCanGo.push_back({0,-1});
}
void PurpleSlime::Set_AttackArea()
{
    /*
     Funkcja ustala wszystkie mozliwe wzgledne punkty na ktorych przeciwnik moze
     wykonac atak
     * */
    whereCanAttack.push_back({1,1});
    whereCanAttack.push_back({-1,-1});
    whereCanAttack.push_back({-1,1});
    whereCanAttack.push_back({1,-1});
}
void PurpleSlime::SetSound()
{
    if(amount>0)return;
    if(!buffer.loadFromFile("../Sounds/plain_hit.ogg"))
    {
        std::cout<<"no sound plain_hit.ogg found"<<std::endl;
    }
    sound.setBuffer(buffer);
}
void PurpleSlime::play_my_sound()
{
    sound.play();
    std::this_thread::sleep_for(std::chrono::milliseconds(buffer.getDuration().asMilliseconds()));
}
PurpleSlime::~PurpleSlime()
{
    amount--;
}