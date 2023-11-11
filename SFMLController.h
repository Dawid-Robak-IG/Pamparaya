//
// Created by dawid on 30.04.2023.
//

#ifndef PAMPARAYA_SFMLCONTROLLER_H
#define PAMPARAYA_SFMLCONTROLLER_H
#include "Pamparaya.h"
#include "Board.h"
#include "SFMLView.h"
#include "Weapon.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <unistd.h>


class SFMLController {
    Board &board;
    Pamparaya &pamparaya;
    SFMLView &view;

    Weapon &sword;
    Weapon &bow;
    Weapon &axe;

    int turns;
public:
    SFMLController(Board &b, Pamparaya &Pam, SFMLView &v, Weapon &s, Weapon &b_, Weapon &a);
    bool can_hero_move(WHERE_TO_GO direction);
    void play(sf::Event &event);
    void hero_attack(sf::RenderWindow &win, sf::Event event);
    void end_of_turn();
    void choose_buf(sf::RenderWindow &win);
    bool choosingBuff(sf::Event &event,const Buff& swordBuff, const Buff& axeBuff, const Buff& bowBuff);
    void put_mountain(sf::Event &event);

    int get_turns() const;
private:
    void try_move_hero(Point pos_modifier, WHERE_TO_GO direction);
    void picking_rock();
};


#endif //PAMPARAYA_SFMLCONTROLLER_H
