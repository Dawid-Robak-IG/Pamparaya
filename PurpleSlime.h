//
// Created by c on 5/24/23.
//

#ifndef PAMPARAYA_PURPLESLIME_H
#define PAMPARAYA_PURPLESLIME_H

#include "Enemy.h"

class PurpleSlime: public Enemy{
    inline static sf::SoundBuffer buffer;
    inline static sf::Sound sound;
    inline static int amount =0;
public:
    PurpleSlime(int x,int y,int boardHeight,int boardWidth, int nr_turns);
    void play_my_sound() override;

private:
    void Set_WhereCanGo();
    void Set_AttackArea();

    void SetSound();
    ~PurpleSlime();
};

#endif //PAMPARAYA_PURPLESLIME_H
