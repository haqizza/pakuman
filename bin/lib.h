#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
// #include"maps.h"

#define ROW 32
#define COL 72

typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
} moves;

typedef struct{
    moves mov;
    int r;
    int c;
} ghost;


moves direction, direction2, gh1_dir;

int car_1r, car_1c;
int car2_1r, car2_1c;
int score_p1;
int score_p2;


char grid[ROW][COL];

void move_car(moves dir);
void move_car2(moves dir);
void food();
void print_grid();
void score();
void init_ghost(ghost *gh,int row, int col);
void move_ghost(ghost *gh);