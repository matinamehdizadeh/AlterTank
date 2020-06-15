//
// Created by MS on 24/12/2018.
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
#ifdef main
#undef main
#endif
SDL_Window* window;
SDL_Renderer* renderer;
int n;
void read_map_file(map* map, char* file_path){
    FILE* file = fopen(file_path, "r");

    fscanf(file, "%d", &n);

    map->wall = malloc(sizeof(wall)*n);
    int i = 0;
    int x1,x2,y1,y2;
    for (i = 0; i < n; ++i) {
        fscanf(file, "%d%d%d%d", &x1, &y1, &x2, &y2);
        ((map->wall)+i)->x1 = x1*88.8;
        ((map->wall)+i)->y1 = y1*85.5;
        ((map->wall)+i)->x2 = x2*88.8;
        ((map->wall)+i)->y2 = y2*85.5;

    }
}

int main() {
    int zarib1x[5],zarib1y[5],zarib2x[5],zarib2y[5],o,zaribfrog1x[8],zaribfrog1y[8],zaribfrog2x[8],zaribfrog2y[8];
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Altertank", 20, 20, 800, 600, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(0));
    int i = 0, j,color1=150,color2=250,color3=250,color4=250,i2=0,a1=250,a2=250,a3=250,a4=250,a5=250,a6=250,a7=250,a8=250,k2,countmine=980;
    int tank1Forward,tank1Left,tank1Right,tank1Fire,tank2Forward,tank2Left,tank2Right,tank2Fire,count2=0,p,emtiazNahayi=0,k1,powerupnumber;
    int count = 0,end1=0;
    int load=0,save = 0;
    tank tank1;
    tank tank2;
    laser laser1;
    laser laser2;
    mine mine1;
    mine mine2;
    frogBomb frogBomb1;
    powerup powerup;
    char chose[20]={"Tank1 Forward"};
    char menu1[20]={"New Game"};
    char menu2[20]={"Load Game"};
    char menu4[20]={"Quit"};
    char menu3[20]={"Chose Keyboard"};
    char score1[10],score2[10];
    tank1.angle = 0;
    SDL_Event event;
    tank1.bullet = malloc(6 * sizeof(Bullet));
    for (j = 0; j < 5; j++) {
        ((tank1.bullet) + j)->isshoot = 0;
    }
    tank2.angle = 0;
    tank2.bullet = malloc(6 * sizeof(Bullet));

    for (j = 0; j < 5; j++) {
        ((tank2.bullet) + j)->isshoot = 0;
    }
    map *map = malloc(sizeof(map));
    read_map_file(map, "mapmap.txt");
    while(1){
        int d=0,emtiaztank1=0,emtiaztank2=0;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        stringRGBA(renderer, 350,230, menu1 ,color1,250 ,250,250);
        stringRGBA(renderer, 345,265, menu2 ,color2,250 ,250,250);
        stringRGBA(renderer, 325,300, menu3 ,color3,250 ,250,250);
        stringRGBA(renderer, 363,335, menu4 ,color4,250 ,250,250);

        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit_window(renderer);
                break;
            } else if (event.type == SDL_KEYDOWN) {
                menu(event, &color1, &color2, &color3, &color4);
                if (event.key.keysym.sym == SDLK_RETURN ) {
                    if(menu(event, &color1, &color2, &color3, &color4) == 1 || menu(event, &color1, &color2, &color3, &color4) == 2){
                        if (save ==1){
                            FILE* fp;
                            fp= fopen("save.txt" , "r");
                            fscanf(fp,"%f %f %f %d %d %d %d\n" ,&tank1.x,&tank1.y,&tank1.angle,&i,&mine1.isshoot , &laser1.isshoot ,&emtiaztank1);
                            fscanf(fp,"%f %f %f %d %d %d %d\n" ,&tank2.x,&tank2.y,&tank2.angle,&i2, &mine2.isshoot , &laser2.isshoot,&emtiaztank2);
                            fscanf(fp,"%d\n",&emtiazNahayi);
                            fscanf(fp,"%d\n",&end1);
                            fclose(fp);
                            load=1;
                            save=0;
                        }

                            if(load!=1) {
                                int emtiaz[10]={0};
                                emtiazNahayi=0;
                                while (1) {
                                    SDL_RenderClear(renderer);
                                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                                    stringRGBA(renderer, 350, 230, "Emtiaz?", 250, 250, 250, 250);
                                    if (SDL_PollEvent(&event)) {
                                        if (event.type == SDL_KEYDOWN) {
                                            if (event.key.keysym.sym == SDLK_RETURN) {
                                                break;
                                            } else
                                                emtiaz[count2] = event.key.keysym.sym;
                                            emtiaz[count2] -= 48;

                                            count2++;
                                        }
                                    }
                                    SDL_RenderPresent(renderer);
                                }
                                for (p = 0; p < count2; p++) {
                                    emtiazNahayi = emtiazNahayi * 10 + emtiaz[p];
                                }
                            }
                                clock_t start, end;
                                int cpu_time_used;

                                start = clock();

                        while (emtiaztank1!= emtiazNahayi && emtiaztank2!=emtiazNahayi){

                                mine1.x = -10;
                                mine2.x = -10;
                                powerup.show = 0;
                                int hide[10] = {0};
                                for (o = 0; o < 5; o++) {
                                    zarib1x[o] = 1;
                                    zarib1y[o] = 1;
                                    zarib2x[o] = 1;
                                    zarib2y[o] = 1;
                                }
                                if (d == 1)
                                    break;
                                if (load!=1) {
                                    mine1.isshoot = 0;
                                    laser1.isshoot = 0;
                                    laser2.isshoot = 0;
                                    mine2.isshoot = 0;
                                    for (i = 0; i < 5; i++) {
                                        (tank1.bullet + i)->isshoot = 0;
                                        (tank2.bullet + i)->isshoot = 0;
                                    }
                                    i = 0;
                                    i2 = 0;
                                    while (1) {

                                        int q, l = 0;
                                        tank1.x = rand() % 800;
                                        tank1.y = rand() % 600;
                                        for (q = 0; q < n; q++) {
                                            if (((map->wall) + q)->x2 == ((map->wall) + q)->x1) {
                                                if ((((map->wall) + q)->y1 <= tank1.y &&
                                                     tank1.y <= ((map->wall) + q)->y2) &&
                                                    ((map->wall) + q)->x1 - 20 <= tank1.x &&
                                                    tank1.x <= ((map->wall) + q)->x1 + 20) {
                                                    l = 1;
                                                    break;
                                                }
                                            } else if (((map->wall) + q)->y1 == ((map->wall) + q)->y2) {
                                                if ((((map->wall) + q)->x1 <= tank1.x &&
                                                     tank1.x <= ((map->wall) + q)->x2) &&
                                                    ((map->wall) + q)->y1 - 20 <= tank1.y &&
                                                    tank1.y <= ((map->wall) + q)->y1 + 20) {
                                                    l = 1;
                                                    break;
                                                }
                                            }

                                        }
                                        if (l == 0) {
                                            break;
                                        }
                                    }

                                    while (1) {
                                        int q, l = 0;
                                        tank2.x = rand() % 800;
                                        tank2.y = rand() % 600;
                                        for (q = 0; q < n; q++) {
                                            if (((map->wall) + q)->x2 == ((map->wall) + q)->x1) {
                                                if ((((map->wall) + q)->y1 <= tank2.y &&
                                                     tank2.y <= ((map->wall) + q)->y2) &&
                                                    ((map->wall) + q)->x1 - 20 <= tank2.x &&
                                                    tank2.x <= ((map->wall) + q)->x1 + 20) {
                                                    l = 1;
                                                    break;
                                                }
                                            } else if (((map->wall) + q)->y1 == ((map->wall) + q)->y2) {
                                                if ((((map->wall) + q)->x1 <= tank2.x &&
                                                     tank2.x <= ((map->wall) + q)->x2) &&
                                                    ((map->wall) + q)->y1 - 20 <= tank2.y &&
                                                    tank2.y <= ((map->wall) + q)->y1 + 20) {
                                                    l = 1;
                                                    break;
                                                }
                                            }

                                        }
                                        if (l == 0) {
                                            break;
                                        }
                                    }
                                }
                            while (1) {
                                countmine++;
                                if (countmine>=1500){
                                    countmine=0;
                                    powerupnumber=rand()%2;
                                    powerup.show=1;
                                    while (1) {
                                        int q, l = 0;
                                        powerup.x = rand() % 800;
                                        powerup.y = rand() % 600;
                                        for (q = 0; q < n; q++) {
                                            if (((map->wall) + q)->x2 == ((map->wall) + q)->x1) {
                                                if ((((map->wall) + q)->y1 <= powerup.y && powerup.y <= ((map->wall) + q)->y2) &&
                                                    ((map->wall) + q)->x1 - 20 <= powerup.x &&
                                                    powerup.x <= ((map->wall) + q)->x1 + 20) {
                                                    l = 1;
                                                    break;
                                                }
                                            } else if (((map->wall) + q)->y1 == ((map->wall) + q)->y2) {
                                                if ((((map->wall) + q)->x1 <= powerup.x && powerup.x <= ((map->wall) + q)->x2) &&
                                                    ((map->wall) + q)->y1 - 20 <= powerup.y &&
                                                    powerup.y <= ((map->wall) + q)->y1 + 20) {
                                                    l = 1;
                                                    break;
                                                }
                                            }

                                        }
                                        if (l == 0) {
                                            break;
                                        }
                                    }
                                }
                                SDL_SetRenderDrawColor(renderer, 255, 240, 220, 255);
                                SDL_RenderClear(renderer);
                                if(laser1.isshoot==1){
                                    draw_laser(renderer,&laser1);
                                }
                                if(laser2.isshoot==1){
                                    draw_laser(renderer,&laser2);
                                }
                                draw_tank(&tank1, renderer, 1);
                                draw_tank(&tank2, renderer, 2);
                                if (powerup.show==1)
                                    draw_powerup(renderer,& powerup,powerupnumber);
                                for (int k = 0; k < n; ++k) {
                                    draw_walls(map->wall, k, renderer);
                                }
                                if (laser1.isshoot==1){
                                    int lasercount=0;
                                    laser1.x1=tank1.x;
                                    laser1.y1=tank1.y;
                                    laser1.x2=tank1.x;
                                    laser1.y2=tank1.y;
                                    while (lasercount!=23){
                                        if (touch_laser(&laser1,&tank2)==1)
                                            break;
                                        lasercount++;
                                        laser1.x2+=(40*sin(tank1.angle));
                                        laser1.y2+=(40*cos(tank1.angle));
                                    }
                                }
                                if (laser2.isshoot==1){
                                    int lasercount=0;
                                    laser2.x1=tank2.x;
                                    laser2.y1=tank2.y;
                                    laser2.x2=tank2.x;
                                    laser2.y2=tank2.y;
                                    while (lasercount!=23){
                                        if (touch_laser(&laser2,&tank1)==1)
                                            break;
                                        lasercount++;
                                        laser2.x2+=(40*sin (tank2.angle));
                                        laser2.y2+=(40*cos(tank2.angle));

                                    }
                                }
                                if (SDL_PollEvent(&event)) {
                                    if (event.type == SDL_QUIT) {
                                        d=1;
                                        quit_window(renderer);
                                        break;
                                    } else if (event.type == SDL_KEYDOWN) {
                                        if (event.key.keysym.sym == SDLK_s){
                                            save =1;
                                            FILE * fp;
                                            fp = fopen("save.txt" , "w");
                                            fprintf(fp,"%f %f %f %d %d %d %d\n" ,tank1.x,tank1.y,tank1.angle,i,mine1.isshoot , laser1.isshoot ,emtiaztank1);
                                            fprintf(fp,"%f %f %f %d %d %d %d\n" ,tank2.x,tank2.y,tank2.angle,i2, mine2.isshoot , laser2.isshoot,emtiaztank2);
                                            fprintf(fp,"%d\n",emtiazNahayi);
                                            fprintf(fp,"%d\n",end1);
                                            fclose(fp);
                                        }
                                        else if (event.key.keysym.sym == tank1Fire) {
                                            if (mine1.isshoot==1) {
                                                fire_mine(&tank1,&mine1);
                                                mine1.isshoot=0;
                                            }
                                            else if (laser1.isshoot==1){
                                                laser1.isshoot=0;
                                                if (touch_laser(&laser1,&tank2)==1){
                                                    emtiaztank1++;
                                                    break;
                                                }
                                            }
                                            else {
                                                if (i < 5) {
                                                    ((tank1.bullet) + i)->angle = tank1.angle;
                                                    fire(&tank1, i, hide, 1);
                                                }
                                                i++;
                                            }
                                        }
                                        else if (event.key.keysym.sym == tank2Fire) {
                                            if (mine2.isshoot==1) {
                                                fire_mine(&tank2,&mine2);
                                                mine2.isshoot=0;
                                            }else if (laser2.isshoot==1){
                                                laser2.isshoot=0;
                                                if (touch_laser(&laser2,&tank1)==1){
                                                    emtiaztank2++;
                                                    break;
                                                }
                                            }else {
                                                if (i2 < 5) {
                                                    ((tank2.bullet) + i2)->angle = tank2.angle;
                                                    fire(&tank2, i2, hide, 2);
                                                }
                                                i2++;
                                            }
                                        } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                                            d = 1;
                                            break;
                                        } else {
                                            move_tank(event, &tank1, map, n, &tank2, tank1Forward, tank1Left,
                                                      tank1Right, tank2Forward, tank2Left, tank2Right);
                                        }
                                    }
                                }
                                if (near_mine(&tank1 , &mine2)==1){
                                    draw_mine(renderer,&mine2);
                                }

                                if(near_mine(&tank2, &mine1)==1){
                                    draw_mine(renderer, &mine1);
                                }
                                draw_bullet(&tank1, renderer);

                                move_bullets_1(&tank1, map, n, zarib1x, zarib1y);
                                draw_bullet(&tank2, renderer);
                                move_bullets_2(&tank2, map, n, zarib2x, zarib2y);
                                SDL_RenderPresent(renderer);
                                hide_1(hide, &tank1);
                                hide_2(hide, &tank2);
                                load=0;
                                if (touch_powerup(&tank1,&mine1,powerupnumber,&powerup,&laser1)==1 && powerup.show==1){
                                    countmine=0;
                                    powerup.show=0;
                                }
                                if (touch_powerup(&tank2,&mine2,powerupnumber,&powerup,&laser2 )==1 && powerup.show==1){
                                    countmine=0;
                                    powerup.show=0;
                                }

                                if (crash(&tank1, &tank2, hide) == 1) {
                                    emtiaztank2++;
                                    break;
                                } else if (crash(&tank1, &tank2, hide) == 2) {
                                    emtiaztank1++;
                                    break;
                                }
                                if (touch_mine(&tank1, &mine2)==1){
                                    emtiaztank2++;
                                    break;
                                }
                            if (touch_mine(&tank2,&mine1)==1){
                                    emtiaztank1++;
                                    break;
                                }
                                //SDL_Delay(1);
                            }
                            if (emtiaztank1==emtiazNahayi || emtiaztank2 == emtiazNahayi){
                                end = clock();
                                cpu_time_used = ((int) (end - start)) / CLOCKS_PER_SEC;
                                int hour=cpu_time_used/3600;
                                cpu_time_used=cpu_time_used%3600;
                                int minute=cpu_time_used/60;
                                int second=cpu_time_used%60;
                                char saat[10]={0};
                                clok(hour,minute,second, saat);
                                for(k1=0;emtiaztank1>0;k1++){
                                    score1[k1]=(emtiaztank1%10)+48;
                                    emtiaztank1=emtiaztank1/10;
                                }
                                for(k2=0;emtiaztank2>0;k2++){
                                    score2[k2]=(emtiaztank2%10)+48;
                                    emtiaztank2=emtiaztank2/10;
                                }
                                char score11[3]={0};
                                char score22[3]={0};
                                k1--;
                                k2--;
                                int k11,k22;
                                for(k11=0;k11<=k1;k11++){
                                    score11[k11]=score1[k1-k11];
                                }
                                for(k22=0;k22<=k2;k22++){
                                    score22[k22]=score2[k2-k22];
                                }
                                if(k1==-1)
                                    score11[0]=48;
                                if(k2==-1)
                                    score22[0]=48;
                                while (1){
                                    SDL_RenderClear(renderer);
                                    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
                                    stringRGBA(renderer, 250, 200, "Score Tank1", 250, 250, 250, 250);
                                    stringRGBA(renderer, 450, 200, "Score Tank2", 250, 250, 250, 250);
                                    stringRGBA(renderer, 280, 300, score11, 250, 250, 250, 250);
                                    stringRGBA(renderer, 490, 300, score22, 250, 250, 250, 250);
                                    stringRGBA(renderer, 370, 400, saat, 250, 250, 250, 250);
                                    SDL_RenderPresent(renderer);
                                    if (SDL_PollEvent(&event)) {
                                        if (event.type == SDL_KEYDOWN) {
                                            d = 1;
                                            break;
                                        }
                                    }
                                }
                        }

                        }
                    }else if (menu(event, &color1, &color2, &color3, &color4) == 4) {
                            quit_window(renderer);
                            break;
                        } else if (menu(event, &color1, &color2, &color3, &color4) == 3) {
                            while (1) {

                                SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
                                SDL_RenderClear(renderer);
                                stringRGBA(renderer, 60, 200, "Tank1 Forward", a1, 250, 250, 250);
                                stringRGBA(renderer, 260, 200, "Tank1 Left", a2, 250, 250, 250);
                                stringRGBA(renderer, 460, 200, "Tank1 Right", a3, 250, 250, 250);
                                stringRGBA(renderer, 660, 200, "Tank1 Fire", a4, 250, 250, 250);
                                stringRGBA(renderer, 60, 400, "Tank2 Forward", a5, 250, 250, 250);
                                stringRGBA(renderer, 260, 400, "Tank2 Left", a6, 250, 250, 250);
                                stringRGBA(renderer, 460, 400, "Tank2 Right", a7, 250, 250, 250);
                                stringRGBA(renderer, 660, 400, "Tank2 Fire", a8, 250, 250, 250);
                                if (SDL_PollEvent(&event)) {
                                    if (event.type == SDL_KEYDOWN) {
                                        count++;
                                        chose_keyboard(event, count, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8,
                                                       &tank1Forward, &tank1Left, &tank1Right, &tank2Forward,
                                                       &tank2Left, &tank2Right, &tank1Fire, &tank2Fire);
                                    }
                                }
                                if (count >= 9) {
                                    break;
                                }


                                SDL_RenderPresent(renderer);
                            }


                        }

                    }
                }
            }
        }



}

