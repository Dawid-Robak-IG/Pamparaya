//
// Created by dawid on 29.04.2023.
//

#ifndef PAMPARAYA_BOARD_H
#define PAMPARAYA_BOARD_H
#include <iostream>
#include <SFML/Audio.hpp>
#include <vector>
#include "Object.h"
#include "Enemy.h"
#include "GreenSlime.h"
#include "PurpleSlime.h"

struct attackingInfo
{
    ENEMIES_TYPIES type;
    Point enemy_pos;
};

class Board{
    int height;
    int width;
    int totalValue; //calkowita wartosc przeciwnikow jaka zostanie dodana na koniec tury
    //                (wartosc- ----> nie ilosc!!!)

    std::vector<std::vector<Object>> board;
    std::vector<std::unique_ptr<Enemy>>enemies;
    std::vector<attackingInfo> enemies_attacks;

    int possible_nr_rocks;
    int rocks_per_turn;

public:
    Board(int height, int width, int start_nr_rocks);
    bool is_on_board(Point point);
    void deal_dmg(int dmg_to_apply,std::vector<Point>area_toDealDmg, int &expToGive);
    void end_of_turn(Point HeroLocation, int &DmgToGive, int nr_turns);
    bool anyEdgePointFree();
    void occupy(int x,int y);
    void occupy(Point point);
    void un_occupy(int x,int y);
    void un_occupy(Point point);
    void Set_Enemies_attacks(Point HeroLocation);
    void Set_To_Kind(Point coordinates, KINDS kind);
    void Rock_Has_Been_Grabbed();
    bool Are_Edges_Mountains();
    bool Put_Erase_Mountain(Point point);

    int get_height() const;
    int get_width() const;
    Object get_Object(int row, int col) const;
    Object get_Object(Point coordinates) const;
    int get_nr_of_enemies() const;
    Point get_enemy_position(int which);
    bool isFieldOccupied(int x,int y);
    bool isFieldOccupied(Point point);
    ENEMIES_TYPIES get_type(int which);
    std::vector<attackingInfo>get_enemies_attacks() const;
    int get_enemy_hp(int which);
    KINDS get_kind(Point coordinates);

    //pomocnicze/debuggowanie
    void cout_occupidity();
    void cout_enemies_pos();
private:
    void set_random_on_edges(int &x,int &y);
    void move_enemies();
    int get_dmg_to_hurt_hero(Point HeroLocation);
    void put_new_rocks();
    void add_new_enemies(int nr_turns);
};


#endif //PAMPARAYA_BOARD_H
