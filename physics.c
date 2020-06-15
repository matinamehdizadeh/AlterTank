//
// Created by MS on 26/12/2018.
//

#include "struckt.h"
#include "view.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "physics.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <time.h>

#define PI 3.14159265
int counterMenu=1;
int touch_wall( tank* tank1,map* map,int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (((map->wall) + i)->x2 == ((map->wall) + i)->x1) {
            if ((((map->wall) + i)->y1 <= tank1->y && tank1->y <= ((map->wall) + i)->y2) &&
                ((map->wall) + i)->x1 - 20 <= tank1->x && tank1->x <= ((map->wall) + i)->x1 + 20) {
                return 1;
            }
        }
            if (((map->wall) + i)->y1 == ((map->wall) + i)->y2) {
                if ((((map->wall) + i)->x1 <= tank1->x && tank1->x <= ((map->wall) + i)->x2) &&
                    ((map->wall) + i)->y1 - 20 <= tank1->y && tank1->y <= ((map->wall) + i)->y1 + 20) {
                    return 1;

                }
            }

        }
        return 0;
    }
int touch_wall_bullet( int x ,int y,map* map,int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (((map->wall) + i)->x2 == ((map->wall) + i)->x1) {
            if ((((map->wall) + i)->y1 <= y && y <= ((map->wall) + i)->y2) &&
                ((map->wall) + i)->x1 - 8 <= x && x <= ((map->wall) + i)->x1 + 8) {
                return 1;
            }
        }
        if (((map->wall) + i)->y1 == ((map->wall) + i)->y2) {
            if ((((map->wall) + i)->x1 <= x && x <= ((map->wall) + i)->x2) &&
                ((map->wall) + i)->y1 - 8 <= y && y <= ((map->wall) + i)->y1 + 8) {
                return 2;

            }
        }

    }
    return 0;
}
void hide_1 (int hide[],tank* tank1) {
    int j;
    for (j = 0; j < 5; j++) {
        if (hide[j] > 0) {
            hide[j]++;
        }
        if (hide[j] > 430) {
            hide[j] = 0;
            (tank1->bullet + j)->isshoot = 0;
        }
    }
}
void hide_2 (int hide[],tank* tank1) {
    int j;
    for (j = 5; j < 10; j++) {
        if (hide[j] > 0)
            hide[j]++;
        if (hide[j] > 430) {
            hide[j] = 0;
            (tank1->bullet + (j-5) )->isshoot = 0;
        }
    }
}
int menu(SDL_Event event, int* color1, int* color2, int* color3 ,int* color4){

    switch (event.key.keysym.sym) {
    case SDLK_UP: {
        if ( counterMenu > 1)
            counterMenu--;
        break;
    }
    case SDLK_DOWN: {
        if(counterMenu <4 )
            counterMenu++;
        break;
    }
    }
    if (counterMenu == 1){
        *color1=150;
        *color2=250;
        *color3=250;
        *color4=250;
    }else if (counterMenu == 2){

        *color1=250;
        *color2=150;
        *color3=250;
        *color4=250;
    }else if (counterMenu == 3){
        *color1=250;
        *color2=250;
        *color3=150;
        *color4=250;
    }else if (counterMenu == 4){
        *color1=250;
        *color2=250;
        *color3=250;
        *color4=150;
    }
    return counterMenu;
}
void chose_keyboard(SDL_Event event, int count ,int* a1,int* a2,int* a3,int* a4,int* a5,int* a6,int* a7,int* a8,int* tank1Forward,int* tank1Left , int* tank1Right,int* tank2Forward,int* tank2Left , int* tank2Right ,int* tank1Fire , int* tank2Fire){
    if (count == 1) {
        *tank1Forward = event.key.keysym.sym;
        *a1=150;
    }else if (count == 2) {
        *tank1Left = event.key.keysym.sym;
        *a2=150;
    }else if (count == 3) {
        *tank1Right = event.key.keysym.sym;
        *a3=150;
    }else if (count == 4) {
        *tank1Fire = event.key.keysym.sym;
        *a4=150;
    }else if (count == 5) {
        *tank2Forward = event.key.keysym.sym;
        *a5=150;
    }else if (count == 6) {
        *tank2Left = event.key.keysym.sym;
        *a6=150;
    }else if (count == 7) {
        *tank2Right = event.key.keysym.sym;
        *a7=150;
    }else if (count == 8) {
        *tank2Fire = event.key.keysym.sym;
        *a8=150;
    }
}
int touch_powerup(tank* tank,mine* mine1,int powerupnumber,powerup* powerup1,laser* laser){
    if( powerup1->x >=(tank->x)-20 && powerup1->x<=(tank->x)+20 && powerup1->y >=(tank->y)-20 && powerup1->y<=(tank->y)+20) {
        if(powerupnumber==0)
            mine1->isshoot=1;
        else
            laser->isshoot=1;
        return 1;
    }
}
void fire_frogbomb(frogBomb* frogBomb1,tank* tank1){
    frogBomb1->x=tank1->x;
    frogBomb1->y=tank1->y;
    frogBomb1->angle=tank1->angle;
}
void explod(frogBomb* frogBomb1,tank* tank1){
    frogBomb1->isshoot = 0;
    if (frogBomb1->click==1) {
        for (int i = 0; i < 8; ++i) {
            ((frogBomb1->bullet) + i)->x = frogBomb1->x;
            ((frogBomb1->bullet) + i)->y = frogBomb1->y;
            ((frogBomb1->bullet) + i)->isshoot = 1;

        }
    }

}
int touch_frogbomb(frogBomb* frogBomb1,tank*tank){
    if (frogBomb1->show==1){
        if ( frogBomb1->x >=(tank->x)-20 && frogBomb1->x <= (tank->x)+20 && frogBomb1->y >= (tank->y)-20 && frogBomb1->y <= (tank->y)+20 )
            return 1;
    }
}
int touch_mine(tank* tank,mine* mine1){
    if ( mine1->x >=(tank->x)-20 && mine1->x<=(tank->x)+20 && mine1->y >=(tank->y)-20 && mine1->y<=(tank->y)+20 )
    return 1;
    else
        return 0;
}
void fire_mine(tank* tank1 , mine* mine){
    mine->x=tank1->x;
    mine->y=tank1->y;

}

int near_mine(tank* tank2, mine* mine) {
    if (mine->x >= (tank2->x) - 60 && mine->x <= (tank2->x) + 60 && mine->y >= (tank2->y) - 60 && mine->y <= (tank2->y) + 60) {
        return 1;

    }
    else
        return 0;
}
void move_tank(SDL_Event event, tank* tank1,map* map,int n, tank* tank2,int tank1Forward,int tank1Left , int tank1Right,int tank2Forward,int tank2Left , int tank2Right) {

    double val = PI / 18;
    if (event.key.keysym.sym == tank1Forward){

        tank1->y = (tank1->y) + 5 * cos(tank1->angle);
        tank1->x = (tank1->x) + 5 * sin(tank1->angle);

        if ( touch_wall (tank1, map, n) == 1  ){
            tank1->y = (tank1->y) - 5 * cos(tank1->angle);
            tank1->x = (tank1->x) - 5 * sin(tank1->angle);
        }


    }else if(event.key.keysym.sym == tank1Right){
        tank1->angle = tank1->angle + val;
    }else if(event.key.keysym.sym == tank1Left){
        tank1->angle = tank1->angle - val;
    }else if(event.key.keysym.sym == tank2Forward){
        tank2->y = (tank2->y) + 5 * cos(tank2->angle);
        tank2->x = (tank2->x) + 5 * sin(tank2->angle);

        if ( touch_wall (tank2, map, n) == 1 ){
            tank2->y = (tank2->y) - 5 * cos(tank2->angle);
            tank2->x = (tank2->x) - 5 * sin(tank2->angle);
        }
    }else if(event.key.keysym.sym == tank2Right){
        tank2->angle = tank2->angle + val;
    }else if(event.key.keysym.sym == tank2Left){
        tank2->angle = tank2->angle - val;
    }


    }

int crash(tank* tank1,tank* tank2, int hide[]){
    int j=0;
    for (j=0;j<5;j++){
        if ((tank1->bullet +j)->isshoot == 1){
            if (((tank1->bullet +j)->x <= (tank2->x) +20 && (tank1->bullet +j)->x >= (tank2->x) -20 && (tank1->bullet +j)->y >= (tank2->y) -20 && (tank1->bullet +j)->y <= (tank2->y) +20 ))
                return 2;
            if (hide[j]>10) {
                if (((tank1->bullet + j)->x <= (tank1->x) + 20 && (tank1->bullet + j)->x >= (tank1->x) - 20 &&
                     (tank1->bullet + j)->y >= (tank1->y) - 20 && (tank1->bullet + j)->y <= (tank1->y) + 20))
                    return 1;
            }
        }
        if ((tank2->bullet +j)->isshoot == 1){
            if (((tank2->bullet + j)->x <= (tank1->x) + 20 && (tank2->bullet + j)->x >= (tank1->x) - 20 &&
                 (tank2->bullet + j)->y >= (tank1->y) - 20 && (tank2->bullet + j)->y <= (tank1->y) + 20))
                return 1;
            if (hide[j+5]>10) {
                if (((tank2->bullet +j)->x <= (tank2->x) +20 && (tank2->bullet +j)->x >= (tank2->x) -20 && (tank2->bullet +j)->y >= (tank2->y) -20 && (tank2->bullet +j)->y <= (tank2->y) +20 ))
                    return 2;

            }

        }
    }
    return 0;
}

int touch_bullet_frogbomb(frogBomb* frogBomb1,tank* tank2) {
    if (frogBomb1->click==1) {
        for (int i = 0; i < 8; ++i) {
            if (((frogBomb1->bullet) + i)->isshoot == 1) {
                if (((frogBomb1->bullet + i)->x <= (tank2->x) + 20 && (frogBomb1->bullet + i)->x >= (tank2->x) - 20 &&
                     (frogBomb1->bullet + i)->y >= (tank2->y) - 20 && (frogBomb1->bullet + i)->y <= (tank2->y) + 20))
                    return 2;
            }
        }
    }
}
void clok(int hour,int minute,int second,char saat[]){
    saat[0]=(hour/10)+48;
    saat[1]=(hour%10)+48;
    saat[2]=':';
    saat[3]=(minute/10)+48;
    saat[4]=(minute%10)+48;
    saat[5]=':';
    saat[6]=(second/10)+48;
    saat[7]=(second%10)+48;
}
void  move_bullet_frogbomb(frogBomb* frogBomb1,map* map,int n , int zaribfrogx[], int zaribfrogy[]){
    for (int j=0;j<8;j++) {
        if ((frogBomb1->bullet + j)->isshoot == 1) {
            if (touch_wall_bullet(((frogBomb1->bullet) + j)->x, ((frogBomb1->bullet) + j)->y, map, n) == 1) {
                zaribfrogx[j] = zaribfrogx[j] * (-1);
            } else if (touch_wall_bullet(((frogBomb1->bullet) + j)->x, ((frogBomb1->bullet) + j)->y, map, n) == 2) {
                zaribfrogy[j] = zaribfrogy[j] * (-1);
            }
            ((frogBomb1->bullet) + j)->x =
                    ((frogBomb1->bullet) + j)->x + (3 * zaribfrogx[j] * sin((PI / 4 ) * j));
            ((frogBomb1->bullet) + j)->y =
                    ((frogBomb1->bullet) + j)->y + (3 * zaribfrogy[j] * cos((PI / 4 ) * j));
        }
    }
}
int touch_laser(laser* laser1,tank* tank2){
    if (laser1->x2>=tank2->x -22 && laser1->x2<= tank2->x +22 && laser1->y2>= tank2->y -22 && laser1->y2<= tank2->y +22)
        return 1;
}
void move_frogbomb(frogBomb* frogBomb1,map* map,int n,tank* tank1,int zaribfrogx[],int zaribfrogy[]) {
            if (frogBomb1->show == 1) {
                if (touch_wall_bullet(frogBomb1->x, frogBomb1->y, map, n) == 1) {
                    frogBomb1->click=1;
                    frogBomb1->isshoot=0;
                    for(int o=0;o<8;o++){
                        zaribfrogx[o]=1;
                        zaribfrogy[o]=1;
                    }
                    explod(frogBomb1, tank1);
                    frogBomb1->show=0;
                } else if (touch_wall_bullet(frogBomb1->x, frogBomb1->y, map, n) == 2) {
                    frogBomb1->click=1;
                    frogBomb1->isshoot=0;
                    for(int o=0;o<8;o++){
                        zaribfrogx[o]=1;
                        zaribfrogy[o]=1;
                    }
                    explod(frogBomb1, tank1);
                    frogBomb1->show=0;
                }
                frogBomb1->x = frogBomb1->x + (3 * sin(frogBomb1->angle));
                frogBomb1->y = frogBomb1->y + (3 * cos(frogBomb1->angle));
            }
    }

void move_bullets_1(tank * tank1,map* map,int n, int zaribx[],int zariby[]) {

    for (int j = 0; j < 5; ++j) {
        if((tank1->bullet + j)->isshoot == 1) {
            if (touch_wall_bullet(((tank1->bullet)+j)->x,((tank1->bullet)+j)->y,map,n) == 1){
                zaribx[j]=zaribx[j]*(-1);
            }else if (touch_wall_bullet(((tank1->bullet)+j)->x,((tank1->bullet)+j)->y,map,n) == 2) {
                zariby[j]=zariby[j]*(-1);
            }
                ((tank1->bullet) + j)->x = ((tank1->bullet) + j)->x + (4 *zaribx[j] * sin(((tank1->bullet) + j)->angle));
                ((tank1->bullet) + j)->y = ((tank1->bullet) + j)->y + (4 *zariby[j] * cos(((tank1->bullet) + j)->angle));
            }
        }
    }
void move_bullets_2(tank * tank1,map* map,int n, int zaribx[],int zariby[]) {

    for (int j = 0; j < 5; ++j) {
        if((tank1->bullet + j)->isshoot == 1) {
            if (touch_wall_bullet(((tank1->bullet)+j)->x,((tank1->bullet)+j)->y,map,n) == 1){
                zaribx[j]=zaribx[j]*(-1);
            }else if (touch_wall_bullet(((tank1->bullet)+j)->x,((tank1->bullet)+j)->y,map,n) == 2) {
                zariby[j]=zariby[j]*(-1);
            }
            ((tank1->bullet) + j)->x = ((tank1->bullet) + j)->x + (3 *zaribx[j] * sin(((tank1->bullet) + j)->angle));
            ((tank1->bullet) + j)->y = ((tank1->bullet) + j)->y + (3 *zariby[j] * cos(((tank1->bullet) + j)->angle));
        }
    }
}