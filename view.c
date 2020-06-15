//
// Created by MS on 24/12/2018.
//

#include "view.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "struckt.h"
#include <unistd.h>
;
;
void draw_powerup(SDL_Renderer* renderer,powerup* mine1,int powerupnumber){
    if (powerupnumber==0)
        thickLineRGBA(renderer , (mine1->x) , (mine1->y) ,mine1->x+20,(mine1->y), 20 , 90, 100, 160, 255);
    else if(powerupnumber==1)
        thickLineRGBA(renderer , (mine1->x) , (mine1->y) ,mine1->x+20,(mine1->y), 20 , 90, 100, 0, 255);
    else
        thickLineRGBA(renderer , (mine1->x) , (mine1->y) ,mine1->x+20,(mine1->y), 20 , 200, 100, 0, 255);
}
void draw_mine(SDL_Renderer* renderer ,mine* mine1){
    filledCircleRGBA(renderer,  mine1->x , mine1->y , 10 , 255,0 , 0, 255);
}
void draw_frogbomb(SDL_Renderer* renderer ,frogBomb* mine1){
    filledCircleRGBA(renderer,  mine1->x , mine1->y , 7 , 255,0 , 0, 255);
}
void draw_tank(tank* tank1,SDL_Renderer* renderer ,int g) {
        int a;
        if(g==1)
            a=10;
        if(g==2)
            a=170;
        filledCircleRGBA(renderer,  tank1->x , tank1->y , 20, 200, a, 10, 255);
        thickLineRGBA(renderer , (tank1->x) , (tank1->y) ,tank1->x+35*sin(tank1->angle),(tank1->y)+35*cos(tank1->angle), 4 ,90, 10, 60, 255);
        filledCircleRGBA(renderer,  tank1->x , tank1->y , 5, 90, 10, 60, 255);
}

void draw_laser(SDL_Renderer* renderer,laser* laser1){
    thickLineRGBA(renderer , (laser1->x1) , (laser1->y1) ,laser1->x2,laser1->y2, 1 ,250, 10, 60, 255);
}
void fire(tank* tank1, int i,int hide[],int x){
    ((tank1->bullet)+i)->x=tank1->x;
    ((tank1->bullet)+i)->y=tank1->y;
    ((tank1->bullet)+i)->isshoot=1;
    if(x==1) {
        hide[i]++;
    }
    if (x==2)
        hide[i+5]++;
}
void draw_bullet(tank* tank1,SDL_Renderer* renderer){
    for (int j = 0; j < 5; j++) {
        if((tank1->bullet + j)->isshoot == 1) {
            filledCircleRGBA(renderer, (tank1->bullet+j)->x , (tank1->bullet+j)->y , 5, 0, 0, 0, 255);
        }
    }
}
void draw_bullet_frogbomb(SDL_Renderer* renderer,frogBomb* frogBomb1) {
    if (frogBomb1->click==1) {
        for (int j = 0; j < 8; j++) {
            if ((frogBomb1->bullet + j)->isshoot == 1) {
                filledCircleRGBA(renderer, (frogBomb1->bullet + j)->x, (frogBomb1->bullet + j)->y, 5, 255, 0, 0, 255);
            }
        }
    }
}

void quit_window(SDL_Renderer* renderer) {
SDL_DestroyRenderer(renderer);
}
 void draw_walls(wall* wall,int i,SDL_Renderer* renderer){

     thickLineRGBA(renderer , ((wall+i)->x1) , ((wall+i)->y1) ,((wall+i)->x2),((wall+i)->y2), 2 ,0, 0, 0, 255);

 }

