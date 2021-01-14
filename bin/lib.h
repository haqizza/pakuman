#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>
#include <wchar.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#define GHOST_NUMBER 5
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
    int death;
} Player;


WINDOW *win;
pthread_mutex_t lock;
pthread_t t_spcfood;
pthread_t t_input1;

Player car1, car2;
Ghosts ghosts[GHOST_NUMBER];

int isStop;
int map;
int full_score;
int max_col, max_row;
int window_col, window_row;
int beg_col, beg_row;
char grid[ROW][COL];



void start_screen();
void load_map();
void init_car(Player *car, int r, int c, char ch);
void init_ghost();
int * rand_number(int limit);
void food();
void *special_food(void *vargp);
void *user_input(void *vargp);
void delay();
void kill_player(Player *car);
void show_score(Player car);
void *move_car1(void *vargp);
void *move_car2(void *vargp);
void kill_player(Player *car);
void *move_ghost(void *i);
void get_ghost_dir(Ghosts *ghost, int move_to);
void ghost_footprint(Ghosts *ghost, char next_c);
void end_screen();
void end_game();
void terminate_ncurses();
void load_map_1();
void load_map_2();