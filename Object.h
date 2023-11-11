//
// Created by dawid on 29.04.2023.
//

#ifndef PAMPARAYA_OBJECT_H
#define PAMPARAYA_OBJECT_H
#include <SFML/Graphics.hpp>
#include <iostream>

enum KINDS{GRASS,ROCK,MOUNTAIN};

class Object {
    int health;
    bool destroyable;
    bool occupied;
    KINDS kind;

public:
    Object(KINDS which);
    void no_longer_occupied();

    int get_health() const;
    bool get_destroyable() const;
    bool get_occupied() const;
    KINDS get_kind() const;

    void put_sth();

    void SetKind(KINDS which);
};


#endif //PAMPARAYA_OBJECT_H
