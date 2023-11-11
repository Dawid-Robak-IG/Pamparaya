//
// Created by dawid on 13.05.2023.
//

#ifndef PAMPARAYA_BOW_H
#define PAMPARAYA_BOW_H

#include "Weapon.h"

class Bow : public Weapon{
    int range;
public:
    Bow(int DMG,int nrOfUse);
    std::vector<Point>get_DealingDmgArea(int x,int y,WHERE_TO_GO direction) override;
    int get_range() const override ;
    Buff get_randBuff() override;
    void apply_buff(Buff buff) override;
private:
    void SetSound();
    void SetExtraBuffsMessages();
};


#endif //PAMPARAYA_BOW_H
