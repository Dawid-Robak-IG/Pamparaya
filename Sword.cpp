//
// Created by dawid on 13.05.2023.
//

#include "Sword.h"

Sword::Sword(int DMG, int nrOfUse) : Weapon(DMG,nrOfUse)
{
    kind_of_weapon=SWORD;
    SetSound();
}
std::vector<Point> Sword::get_DealingDmgArea(int x, int y, WHERE_TO_GO direction)
{
    /*
     Funckja zwraca obszar na ktorym zadawane sa obrazenia w zaleznosci od podanych parametrow
     x i y to wspolrzedne na planszy ktore okreslaja miejsce w ktore uderzylismy
     direction okresla w ktora strone uderzyl bohater
     funkcja bedzie zwracac vector ktory bedzie zawierac jedna wartosc: punkt {x,y}
    */
    std::vector<Point> area;
    area.push_back({x,y});
    return area;
}
Buff Sword::get_randBuff()
{
    /*
     funckja zwroci losowe ulepszenie, z losowymi warotsciami:
     mozliwe ulepszenia:
     -Damage increase: [2,6],
     -Uses per turn increase: [1,2]
     main_value opisuje wartosci ulepszenia,
     za to ilosci dodatkowych akcji dla bohater to [-1,1]
      */
    int k=rand()%buffs_messages.size();
    int main_value=0;
    if(buffs_messages[k]=="Damage increase: ")
        main_value=2+rand()%5;
    else if(buffs_messages[k]=="Uses per turn increase: ")
        main_value=1+rand()%2;
    return {buffs_messages[k],main_value,-1+rand()%3};
}
void Sword::SetSound()
{
    /*
     Ustawia dzwiek ktory wydaje bron
     * */
    if(!buffer.loadFromFile("../Sounds/sword.ogg"))
    {
        std::cout<<"No sound sword"<<std::endl;
    }
    sound.setBuffer(buffer);
}