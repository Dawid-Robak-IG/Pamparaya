//
// Created by dawid on 13.05.2023.
//

#ifndef PAMPARAYA_ENEMY_H
#define PAMPARAYA_ENEMY_H

#include "Point.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>

enum ENEMIES_TYPIES{GREEN_SLIME,PURPLE_SLIME};

/*
 Klasa abstrakcyjna
 * */
class Enemy {
protected:
    int hp;
    int dmg;
    int value; //how powerful and how much exp gives
    int boardHeight;
    int boardWidth;
    ENEMIES_TYPIES type;
    Point position;
    std::vector<Point>whereCanAttack;
    std::vector<Point>whereCanGo;

public:
    Enemy(int x,int y,int boardHeight,int boardWidth);
    void be_attacked(int dmgToHandle);

    ENEMIES_TYPIES get_type() const;
    Point get_position() const;
    int get_hp() const;
    int get_dmg() const;
    Point get_rand_whereCanGo() const;
    std::vector<Point>get_AttackArea() const;
    Point get_whereCouldAttack(int which);
    int get_value() const;

    void SetPosition(Point point);

    virtual void play_my_sound()=0;

private:
    virtual void Set_WhereCanGo()=0;
};


#endif //PAMPARAYA_ENEMY_H
