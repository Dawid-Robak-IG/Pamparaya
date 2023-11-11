//
// Created by dawid on 13.05.2023.
//

#ifndef PAMPARAYA_GREENSLIME_H
#define PAMPARAYA_GREENSLIME_H

#include "Enemy.h"

class GreenSlime: public Enemy{
    inline static sf::SoundBuffer buffer;
    inline static sf::Sound sound;
    inline static int amount =0;
public:
    GreenSlime(int x,int y,int boardHeight,int boardWidth, int nr_turns);
    void play_my_sound() override;

private:
    void Set_WhereCanGo();
    void Set_AttackArea();

    void SetSound();
    ~GreenSlime();
};

#endif //PAMPARAYA_GREENSLIME_H
