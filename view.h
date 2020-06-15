//
// Created by MS on 24/12/2018.


#ifndef ALTERTANK_VIEW_H
#define ALTERTANK_VIEW_H

#include "struckt.h"
#include "view.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "physics.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>


void draw_tank(tank *,SDL_Renderer* renderer,int g);
void quit_window();
void fire(tank* tank, int i,int hide[],int x);
void draw_powerup(SDL_Renderer* renderer,powerup* mine1,int powerupnumber);
void draw_laser(SDL_Renderer* renderer,laser* laser1);
void draw_mine(SDL_Renderer* renderer ,mine* mine1);
void draw_frogbomb(SDL_Renderer* renderer ,frogBomb* mine1);
void draw_bullet(tank* tank1,SDL_Renderer* renderer);
void draw_walls(wall* wall,int i,SDL_Renderer* renderer);
#endif //ALTERTANK_VIEW_H
