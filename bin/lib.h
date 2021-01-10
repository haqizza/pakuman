#include <stdlib.h>
// #include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>
#define GHOST_NUMBER 5
#define ROW 32
#define COL 72
// #include<windows.h>
// #include"maps.h"


typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
} moves;

typedef struct{
    int r;
    int c;
    char foot;
    moves dir;
} Ghosts;

typedef struct{
    int r;
    int c;
    char ch;
    moves dir;
    int score;
} Player;


WINDOW *win;
pthread_mutex_t lock;

Player car1, car2;
Ghosts ghosts[GHOST_NUMBER];
int isStop;
int max_col, max_row;
char grid[ROW][COL];

void loadMap();
void init_car(Player *car, int r, int c, char ch);
void init_ghost();
int randNumber();
void food();
void *user1Input(void *arg);
void *user2Input(void *arg);
void delay();
void kill(Player *car);
void show_score(Player car);
void *move_car1(void *arg);
void *move_car2(void *arg);
void *move_ghost(void *i);