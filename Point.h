//
// Created by dawid on 17.06.2023.
//

#ifndef PAMPARAYA_POINT_H
#define PAMPARAYA_POINT_H

struct Point{
    int x;
    int y;
    Point operator+(Point other);
    Point operator/(int factor);
    bool operator==(Point other);
};


#endif //PAMPARAYA_POINT_H
