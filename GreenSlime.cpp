//
// Created by dawid on 13.05.2023.
//

#include "GreenSlime.h"

GreenSlime::GreenSlime(int x, int y,int boardHeight,int boardWidth, int nr_turns):
                        Enemy(x,y,boardHeight,boardWidth)
{
    hp=5+nr_turns/10;
    value=1;
    dmg=2;
    type=GREEN_SLIME;
    Set_WhereCanGo();
    Set_AttackArea();

    SetSound();
    amount++;
}

void GreenSlime::Set_WhereCanGo()
{
    /*
     Funkcja ustala wszystkie mozliwe zmiany polozenia przeciwnika jakie moze wykonac przeciwnik
     * */
    whereCanGo.push_back({1,0});
    whereCanGo.push_back({-1,0});
    whereCanGo.push_back({0,1});
    whereCanGo.push_back({0,-1});
}
void GreenSlime::Set_AttackArea()
{
    /*
     Funkcja ustala wszystkie mozliwe wzgledne punkty na ktorych przeciwnik moze
     wykonac atak
     * */
    whereCanAttack.push_back({1,0});
    whereCanAttack.push_back({-1,0});
    whereCanAttack.push_back({0,1});
    whereCanAttack.push_back({0,-1});
}
void GreenSlime::SetSound()
{
    if(amount>0)return;
    if(!buffer.loadFromFile("../Sounds/slimy.ogg"))
    {
        std::cout<<"no sound slimy.ogg found"<<std::endl;
    }
    sound.setBuffer(buffer);
}
void GreenSlime::play_my_sound()
{
    sound.play();
    std::this_thread::sleep_for(std::chrono::milliseconds(buffer.getDuration().asMilliseconds()));
}
GreenSlime::~GreenSlime()
{
    amount--;
}