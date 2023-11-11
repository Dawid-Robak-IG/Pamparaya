//
// Created by dawid on 13.05.2023.
//

#include "Enemy.h"

Enemy::Enemy(int x, int y,int boardHeight,int boardWidth)
{
    position={x,y};
    hp=1;
    dmg=1;
    this->boardHeight=boardHeight;
    this->boardWidth=boardWidth;
    type=GREEN_SLIME;
}
void Enemy::be_attacked(int dmgToHandle)
{
    hp-=dmgToHandle;
}

int Enemy::get_hp() const
{
    return hp;
}
int Enemy::get_dmg() const
{
    return dmg;
}

ENEMIES_TYPIES Enemy::get_type() const
{
    return type;
}

Point Enemy::get_position() const
{
    return position;
}
Point Enemy::get_rand_whereCanGo() const
{
    /*
     Funkcja zwroci losowa zmiane polozenia przeciwnika
     nie sa to nowe losowe wspolrzedne przeciwnika
     a jego mozliwa zmiana
     np. enemy ma wspol (5,5) i moze sie ruszac tylko o jedno pole w prawo
     wtedy ta funkcja zawsze zwroci (1,0)
     * */
    return whereCanGo[rand()%whereCanGo.size()];
}
std::vector<Point> Enemy::get_AttackArea() const
{
    /*
     Zwraca vector wspolrzednym ktory informuje o wzglednych punktach wzgledem pozycji
     przeciwnika ktore takowy przeciwnik moze zaatakowac
     * */
    return whereCanAttack;
}
Point Enemy::get_whereCouldAttack(int which)
{
    /*
     Zwraca rzeczywiste wspolrzedne na boardzie na ktore przeciwnik moze wyprowadzic ataka
     * */
    return whereCanAttack[which]+position;
}
int Enemy::get_value() const
{
    return value;
}
void Enemy::SetPosition(Point point)
{
    /*
      ustala nowe wspolrzedne przeciwnika na boardzie
     * */
    position=point;
}