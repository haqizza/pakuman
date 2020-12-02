#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>

#define ROW 21
#define COL 72

enum move {UP,DOWN,LEFT,RIGHT,STOP}direction, direction2;
//enum move2 {UP2,DOWN2,LEFT2,RIGHT2,STOP2}direction2;
//enum ghost_move {UP1,DOWN1,LEFT1,RIGHT1,STOP1} ghost1_dir,ghost2_dir;
//enum move ghost1_dir,ghost2_dir;

void move_car(enum move dir);
void move_car2(enum move dir);
// void ghost1_direction();
// void ghost2_direction();
// void ghost1_move(enum ghost_move g1_dir);
// void ghost2_move(enum ghost_move g2_dir);

int car_1r,car_1c,car_2r,car_2c;
int car2_1r,car2_1c,car2_2r,car2_2c;
// int ghost1_r, ghost1_c;
// int ghost2_r,ghost2_c,ghost11,ghost22;

void print_grid();