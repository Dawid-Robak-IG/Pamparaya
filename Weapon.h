//
// Created by dawid on 07.05.2023.
//

#ifndef PAMPARAYA_WEAPON_H
#define PAMPARAYA_WEAPON_H
#include <iostream>
#include <vector>
#include <random>
#include <SFML/Audio.hpp>
#include "Point.h"

enum WEAPON{SWORD,BOW,AXE};
enum WHERE_TO_GO{UP,DOWN,RIGHT,LEFT,STANDING};

struct Buff{
    std::string message;
    int value;//main
    int actions_value;
};

/*
 * Klasa abstrakcyjna
 * Jest ona potrzebna do dziedziczenia po niej
 * Dla takich klas jak: sword, axe, bow
 * Ustala one pewne parametry ktore beda wspolne dla kazdej broni
 * */
class Weapon {
    int current_uses;
protected:
    int damage;
    int uses_per_turn;
    WEAPON kind_of_weapon;
    std::vector<std::string> buffs_messages;

    sf::SoundBuffer buffer;
    sf::Sound sound;

public:
    Weapon(int DMG,int nrOfUse);
    void end_of_turn();
    void DecreaseCurrentUses();
    virtual void apply_buff(Buff buff);
    void play_my_sound();

    virtual WEAPON get_kind() const;
    int get_dmg() const;
    int get_current_number_of_use() const;
    int get_number_of_use() const;

    virtual std::vector<Point>get_DealingDmgArea(int x,int y,WHERE_TO_GO direction) = 0;
    virtual int get_range() const;
    virtual Buff get_randBuff()=0;


protected:
    virtual void SetBuffsMessages();
};


#endif //PAMPARAYA_WEAPON_H
