//
// Created by dawid on 30.04.2023.
//

#ifndef PAMPARAYA_PAMPARAYA_H
#define PAMPARAYA_PAMPARAYA_H
#include "Weapon.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class Pamparaya {
    int health;
    int nr_of_actions;
    int current_nr_actions;
    int sight;
//    int row; //on board
//    int column; //on board
    Point coords; //coordinates on board
    int lvl;
    int exp;
    int picked_rocks;
    int rocksForMountain;

    Weapon *weapon;
    WHERE_TO_GO appearance;

    int board_height;
    int board_width;

    // points depeding on where hero is where mouse can be clicked to trigger weapon action
    std::vector<Point> useable_points;

    sf::SoundBuffer buffer;
    sf::Sound sound;

public:
    Pamparaya(int hp,int nr_of_actions, int board_height, int board_width,Weapon &w);

    bool does_attack(int row_attacked,int col_attacked);
    bool does_put_mountain(int row_attacked,int col_attacked);
    void move(WHERE_TO_GO direction);
    void end_of_turn();
    void SetAppearance(int attacking_row,int attacking_col);
    void ResetAppearance(WHERE_TO_GO how_to_look);
    void ChangeWeapon(Weapon &w);
    void DidAction();
    Weapon*  get_weapon();
    void be_attacked(int dmgToTake);
    bool does_lvlUp(int expToIncrease);
    void apply_buff(Buff buff);
    void picked_rock();
    void have_put_mountain();

    void play_my_sound();

    int get_sight() const;
    int get_row() const;
    int get_col() const;
    int get_nr_of_actions() const;
    int get_current_nr_actions() const;
    WEAPON get_choosen_weapon();
    WHERE_TO_GO get_appearance();
    int get_health() const;
    int get_exp() const;
    int get_lvl() const;
    int get_exp_tolvlup() const;
    Point get_position() const;
    int get_picked_rocks() const;
    int get_rocks_for_mountain() const;
    std::vector<Point> get_useablePoints() const;
private:
    void SetUseablePoints();
    void SetSound();
};


#endif //PAMPARAYA_PAMPARAYA_H
