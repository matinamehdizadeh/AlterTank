//
// Created by MS on 25/12/2018.
//

#ifndef ALTERTANK_STRUCK_H
#define ALTERTANK_STRUCK_H
#include <stdbool.h>
typedef  struct {
    float x1,y1,x2,y2;
} wall;

typedef struct {
    float x,y;
    int isshoot;
    double angle;
} Bullet;
typedef struct {
    float x,y;
    int isshoot;
}mine;
typedef struct {
    float x,y;
    int isshoot;
    int click;
    Bullet* bullet;
    double angle;
    int show;
}frogBomb;
typedef struct {
    float x1,y1,x2,y2;
    int isshoot;
}laser;
typedef struct {
    float x;
    float y;
    double angle;
    Bullet* bullet;
} tank;
typedef struct {
    tank* tank1;
    wall* wall;
}map;
typedef struct {
    float x,y;
    int show ;
}powerup;

#endif //ALTERTANK_STRUCK_H
