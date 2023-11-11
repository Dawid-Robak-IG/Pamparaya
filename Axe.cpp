//
// Created by dawid on 13.05.2023.
//

#include "Axe.h"

Axe::Axe(int DMG, int nrOfUse) : Weapon(DMG,nrOfUse)
{
    kind_of_weapon=AXE;
    SetSound();
}
void Axe::SetSound()
{
    /*
     Ustawia dzwiek ktory wydaje bron
     * */
    if(!buffer.loadFromFile("../Sounds/axe.ogg"))
    {
        std::cout<<"No sound axe"<<std::endl;
    }
    sound.setBuffer(buffer);
}
std::vector<Point> Axe::get_DealingDmgArea(int x, int y, WHERE_TO_GO direction)
{
    /*
     Funckja zwraca obszar na ktorym zadawane sa obrazenia w zaleznosci od podanych parametrow
     x i y to wspolrzedne na planszy ktore okreslaja miejsce w ktore uderzylismy
     direction okresla w ktora strone uderzyl bohater
     funkcja bedzie zwracac vector ktory bedzie zawierac punkt {x,y} oraz jego okolice
     czyli dla direction==UP punkty {x,y},{x-1,y} oraz {x+1,y}
    */
    std::vector<Point> area;
    area.push_back({x,y});
    if(direction==UP or direction==DOWN)
    {
        area.push_back({x-1,y});
        area.push_back({x+1,y});
    }
    else if(direction==RIGHT or direction==LEFT)
    {
        area.push_back({x,y-1});
        area.push_back({x,y+1});
    }
    return area;
}
Buff Axe::get_randBuff()
{
    /*
     funckja zwroci losowe ulepszenie, z losowymi warotsciami:
     mozliwe ulepszenia:
     -Damage increase: [0,8],
     -Uses per turn increase: [0,1]
     main_value opisuje wartosci ulepszenia,
     za to ilosci dodatkowych akcji dla bohater to [-1,1]
      */
    int k=rand()%buffs_messages.size();
    int main_value=0;
    if(buffs_messages[k]=="Damage increase: ")
        main_value=rand()%8;
    else if(buffs_messages[k]=="Uses per turn increase: ")
        main_value=rand()%1;
    return {buffs_messages[k],main_value,-1+rand()%3};
}