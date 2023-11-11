//
// Created by dawid on 13.05.2023.
//

#include "Bow.h"

Bow::Bow(int DMG, int nrOfUse): Weapon(DMG,nrOfUse)
{
    range=2;
    kind_of_weapon=BOW;
    SetExtraBuffsMessages();
    SetSound();
}

std::vector<Point> Bow::get_DealingDmgArea(int x, int y, WHERE_TO_GO direction)
{
    /*
     Funckja zwraca obszar na ktorym zadawane sa obrazenia w zaleznosci od podanych parametrow
     x i y to wspolrzedne na planszy ktore okreslaja miejsce w ktore uderzylismy
     direction okresla w ktora strone uderzyl bohater
     funkcja bedzie zwracac vector ktory bedzie zawierac punkt {x,y} oraz jego okolice (zzleznie od range'a)
     czyli dla direction==UP punkty {x,y},{x,y-1} dla rnage'a=2
    */
    std::vector<Point> area;
    if(direction==UP)
    {
        for(int i=0;i<range;i++)
            area.push_back({x,y-i});
    }
    else if(direction==DOWN)
    {
        for(int i=0;i<range;i++)
            area.push_back({x,y+i});
    }
    else if(direction==RIGHT)
    {
        for(int i=0;i<range;i++)
            area.push_back({x+i,y});
    }
    else if(direction==LEFT)
    {
        for(int i=0;i<range;i++)
            area.push_back({x-i,y});
    }
    return area;
}
void Bow::SetExtraBuffsMessages()
{
    /*
     Funkcja ma na celu dodanie dodatkowego mozliwego do wylosowania w przyszlosci bonusu
     Dzieki niej bedzie mozliwosc zwiekszenia zasiegu luku
     * */
    buffs_messages.emplace_back("Range Increase: ");
}
Buff Bow::get_randBuff()
{
    /*
     funckja zwroci losowe ulepszenie, z losowymi warotsciami:
     mozliwe ulepszenia:
     -Damage increase: [0,3],
     -Uses per turn increase: [0,1]
     -Range Increase: [-1,1]
     main_value opisuje wartosci ulepszenia,
     za to ilosci dodatkowych akcji dla bohater to [-1,1]
      */
    int k=rand()%buffs_messages.size();
    int main_value=0;
    if(buffs_messages[k]=="Damage increase: ")
        main_value=rand()%3;
    else if(buffs_messages[k]=="Uses per turn increase: ")
        main_value=-1+rand()%2;
    else if(buffs_messages[k]=="Range Increase: ")
        main_value=1+rand()%2;
    return {buffs_messages[k],main_value,-1+rand()%3};
}
void Bow::apply_buff(Buff buff)
{
    /*
     Funckja zmienia poszczegolne parametry broni
     buff wyznacza jaki parametr broni ma zostac zmieniony oraz o jaka wartosc zostanie zmieniony
     mozliwe zmienienie:
     -damage
     -uses_per_turn
     -range
     * */
    if(buff.message.compare("Damage increase: ")==0)damage+=buff.value;
    else if(buff.message.compare("Uses per turn increase: ")==0)uses_per_turn+=buff.value;
    else if(buff.message.compare("Range Increase: ")==0)range+=buff.value;
}
void Bow::SetSound()
{
    /*
     Ustawia dzwiek ktory wydaje bron
     * */
    if(!buffer.loadFromFile("../Sounds/bow.ogg"))
    {
        std::cout<<"No sound bow"<<std::endl;
    }
    sound.setBuffer(buffer);
}


int Bow::get_range() const
{
    return range;
}