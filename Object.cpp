//
// Created by dawid on 29.04.2023.
//

#include "Object.h"

Object::Object(KINDS which)
{
    SetKind(which);
}

void Object::put_sth()
{
    /*Sprawia ze ten obiekt jest zajety (pole jest zajete)  */
    occupied=true;
}
void Object::no_longer_occupied()
{
    /*Sprawia ze ten obiekt jest wolny(pole jest niezajete)  */
    occupied=false;
}
void Object::SetKind(KINDS which)
{
    /*
     which jest to rodzaj obiektu ktory ma zostac ustawiony
     funckja ustala wszystkie parametry obiektu na te ktory charakteryzuja kazdy
     rodzaj obiektu
     * */
    kind=which;
    if(which==ROCK)
    {
        health=5;
        destroyable=true;
    }
    else if(which==MOUNTAIN)
    {
        health=-1;
        occupied=true;
        destroyable=false;
    }
    else if(which==GRASS)
    {
        health=-1;
        destroyable=true;
    }
}

int Object::get_health() const
{
    return health;
}

bool Object::get_destroyable() const
{
    return destroyable;
}

bool Object::get_occupied() const
{
    return occupied;
}
KINDS Object::get_kind() const
{
    return kind;
}

