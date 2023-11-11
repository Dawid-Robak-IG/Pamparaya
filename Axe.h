//
// Created by dawid on 13.05.2023.
//

#ifndef PAMPARAYA_AXE_H
#define PAMPARAYA_AXE_H

#include "Weapon.h"

class Axe :public Weapon{
public:
    Axe(int DMG,int nrOfUse);
    std::vector<Point>get_DealingDmgArea(int x,int y,WHERE_TO_GO direction) override;
    Buff get_randBuff() override ;
private:
    void SetSound();
};


#endif //PAMPARAYA_AXE_H
