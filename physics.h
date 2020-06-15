//
// Created by MS on 26/12/2018.
//

#ifndef ALTERTANK_PHYSICS_H
#define ALTERTANK_PHYSICS_H

#include "struckt.h"
#include <SDL.h>
void chose_keyboard(SDL_Event event, int count ,int* a1,int* a2,int* a3,int* a4,int* a5,int* a6,int* a7,int* a8,int* tank1Forward,int* tank1Left , int* tank1Right,int* tank2Forward,int* tank2Left , int* tank2Right ,int* tank1Fire , int* tank2Fire);
void move_tank(SDL_Event , tank * ,map* map,int n, tank* tank2,int tank1Forward,int tank1Left , int tank1Right,int tank2Forward,int tank2Left , int tank2Right );
void move_bullets_1(tank *,map* map,int n,int zaribx[],int zariby[]);
void move_bullets_2(tank * tank1,map* map,int n, int zaribx[],int zariby[]);
int menu(SDL_Event event, int* color1, int* color2, int* color3 ,int* color4);
int touch_wall(tank* tank1,map* map,int n);
int touch_wall_bullet( int x ,int y,map* map,int n);
void hide_1(int hide[],tank* tank1);
void hide_2(int hide[],tank* tank1);
int crash(tank* tank1,tank* tank2,int hide[]);
void clok (int hour,int minute,int second,char saat[]);
int touch_powerup(tank* tank,mine* mine1,int powerupnumber,powerup* powerup1,laser* laser);
int touch_laser(laser* laser1,tank* tank2);
int near_mine(tank* tank2, mine* mine);
void fire_mine(tank* tank1 , mine* mine);
void fire_frogbomb(frogBomb* frogBomb1,tank* tank1);
void explod(frogBomb* frogBomb1,tank* tank1);
void draw_bullet_frogbomb(SDL_Renderer* renderer,frogBomb* frogBomb1);
void move_frogbomb(frogBomb* frogBomb1,map* map,int n,tank* tank1,int zaribfrogx[],int zaribfrogy[]);
int touch_bullet_frogbomb(frogBomb* frogBomb1,tank* tank2);
int touch_frogbomb(frogBomb* frogBomb1,tank*tank1);
void  move_bullet_frogbomb(frogBomb* frogBomb1,map* map,int n , int zaribfrogx[], int zaribfrogy[]);
void fire_laser();
int touch_mine(tank* tank,mine* mine1);
#endif //ALTERTANK_PHYSICS_H
