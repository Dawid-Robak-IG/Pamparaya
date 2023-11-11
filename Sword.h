//
// Created by dawid on 13.05.2023.
//

#ifndef PAMPARAYA_SWORD_H
#define PAMPARAYA_SWORD_H

#include "Weapon.h"

class Sword :public Weapon{
public:
    Sword(int DMG,int nrOfUse);
    std::vector<Point>get_DealingDmgArea(int x,int y,WHERE_TO_GO direction) override;
    Buff get_randBuff() override;
private:
    void SetSound();
};


#endif //PAMPARAYA_SWORD_H
