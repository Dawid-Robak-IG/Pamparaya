//
// Created by dawid on 17.06.2023.
//

#include "Point.h"

Point Point::operator+(Point other)
{
    return {x+other.x,y+other.y};
}
bool Point::operator==(Point other)
{
    if(x==other.x and y==other.y)return true;
    return false;
}
Point Point::operator/(int factor)
{
    return {x/2, y/2};
}