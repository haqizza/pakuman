#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>

#define ROW 32
#define COL 72

typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
} moves;

typedef struct ghost{
    moves mov;
    int r;
    int c;
} ghost;


moves direction, direction2, gh1_dir;



void move_car(moves dir);
void move_car2(moves dir);

int car_1r, car_1c;
int car2_1r, car2_1c;
int gh_1r,gh_1c;


char grid[ROW][COL]= {
"***********************************************************************",
"*G                D                                                   *",
"*   ***************         *******   ******        ***************   *",
"*   ***************         *******   ******        ***************   *",
"*   ***************         *******   ******        ***************   *",
"*   *******                 *******   ******                *******   *",
"*   *******                 *******   ******                *******   *",
"*   *******                 *******   ******                *******   *",
"*   *******                 *******   ******                *******   *",
"*                                @                                    *",
"*                   **************    **************                  *",
"*                   **************    **************                  *",
"*                   **************    **************                  *",
"*                   **************    **************                  *",
"*                   **************    **************                  *",
"*     ****************************    ******************************  *",
"*     ****************************    ******************************  *",
"*     ****************************    ******************************  *",
"*     ****************************    ******************************  *",
"*                                                                     *",
"*                                                                     *",
"*                                                                     *",
"*                                                                     *",
"*    **********************                 **********************    *",
"*    **********************                 **********************    *",
"*    **********************                 **********************    *",
"*    ***********                                       ***********    *",
"*    ***********                                       ***********    *",
"*    ***********                                       ***********    *",
"*                                                                     *",
"*                                                                     *",
"***********************************************************************"};

void food() {
    int i, j;
    for(i=0;i<ROW;i++) {
        for(j=0;j<COL;j++) {
            if(grid[i][j] == ' ') {
                grid[i][j] = '.';
            }
        }
    }
}

void print_grid();

int score_p1 = 0;
int score_p2 = 0;
ghost ghost1;

void score() {
    if(grid[car_1r][car_1c] == '.') {
        score_p1++;
    } 
    if(grid[car2_1r][car2_1c] == '.') {
        score_p2++;
    }
}

void delay(void){
    int delay_i, delay_j;
    for(delay_i=0;delay_i<4000;delay_i++) {
        for(delay_j=0;delay_j<10000;delay_j++) {}
    } 
}

int main()
{
    direction = STOP;
    direction2 = STOP;
    gh1_dir = STOP;
    int i, count = 1;

    ghost1.r = 2;
    ghost1.c = 2;
    

    car_1r = 9;
    car_1c = 33;
    car2_1r = 1;
    car2_1c = 18;
    
    char ch;
    food();
    print_grid();

    while(count){
        if(_kbhit()){
            ch = _getch();

            switch(ch){
                case 'd':

                        direction=RIGHT;
                        break;


                case 'a':

                        direction=LEFT;
                        break;


                case 'w':

                        direction = UP;
                        break;


                case 's':

                        direction = DOWN;
                        break;

                case 'l':

                        direction2 = RIGHT;
                        break;

                case 'j':

                        direction2 = LEFT;
                        break;

                case 'i':

                        direction2 = UP;
                        break;

                case 'k':

                        direction2 = DOWN;
                        break;

                default:;

            }
        }

        score();
        move_car(direction);
        move_car2(direction2);
        move_ghost(ghost1);
        system("cls");
        print_grid();
        delay();
    }
return 0;
}

void print_grid()
{
    int i;

    for(i=0;i<ROW;i++)
    printf("%s\n",grid[i]);

    printf("\nScore P1: %d\n", score_p1);
    printf("Score P2: %d\n", score_p2);
    printf("(X,Y) P1 : (%d,%d)\n", car_1r, car_1c);
    printf("(X,Y) P2 : (%d,%d)\n", car2_1r, car2_1c);

}
void move_car(moves dir)
{
    if(dir==UP)
    {
        if(grid[car_1r-1][car_1c]!= '*' & grid[car_1r-1][car_1c]!= 'D')
        {
           grid[car_1r][car_1c]=' ';
           if(grid[car_1r-1][car_1c] == '.') {
                score_p1++;
           }
           grid[car_1r-1][car_1c]='@';
           car_1r--;
        }
    }
    else if(dir==DOWN)

    {
        if(grid[car_1r+1][car_1c]!= '*' & grid[car_1r+1][car_1c]!= 'D')
      {
           grid[car_1r][car_1c]=' ';
           if(grid[car_1r+1][car_1c] == '.') {
                score_p1++;
           }
           grid[car_1r+1][car_1c]='@';
           car_1r++;
      }
    }
    if(dir==LEFT)
    {
       if(grid[car_1r][car_1c-1]!= '*' & grid[car_1r][car_1c-1]!= 'D')
       {
           grid[car_1r][car_1c]=' ';
           if(grid[car_1r][car_1c-1] == '.') {
                score_p1++;
           }
           grid[car_1r][car_1c-1]='@';
           car_1c--;
      }
    }
    else if(dir==RIGHT)

    {
       if(grid[car_1r][car_1c+1]!= '*' & grid[car_1r][car_1c+1]!= 'D')
       {
           grid[car_1r][car_1c]=' ';
           if(grid[car_1r][car_1c+1] == '.') {
                score_p1++;
           }
           grid[car_1r][car_1c+1]='@';

           car_1c++;
       }
    }
}

void move_car2(moves dir)
{
    if(dir==UP)
    {
        if(grid[car2_1r-1][car2_1c]!= '*' & grid[car2_1r-1][car2_1c]!= '@')
        {
           grid[car2_1r][car2_1c]=' ';
           if(grid[car2_1r-1][car2_1c] == '.') {
                score_p2++;
           }
           grid[car2_1r-1][car2_1c]='D';
           car2_1r--;
        }
    }
    else if(dir==DOWN)

    {
        if(grid[car2_1r+1][car2_1c]!= '*' & grid[car2_1r+1][car2_1c]!= '@')
      {
           grid[car2_1r][car2_1c]=' ';
           if(grid[car2_1r+1][car2_1c] == '.') {
                score_p2++;
           }
           grid[car2_1r+1][car2_1c]='D';
           car2_1r++;
      }
    }
    if(dir==LEFT)
    {
       if(grid[car2_1r][car2_1c-1]!= '*' & grid[car2_1r][car2_1c-1]!= '@')
       {
           grid[car2_1r][car2_1c]=' ';
           if(grid[car2_1r][car2_1c-1] == '.') {
                score_p2++;
           }
           grid[car2_1r][car2_1c-1]='D';
           car2_1c--;
      }
    }
    else if(dir==RIGHT)

    {
       if(grid[car2_1r][car2_1c+1]!= '*' & grid[car2_1r][car2_1c+1]!= '@')
       {
           grid[car2_1r][car2_1c]=' ';
           if(grid[car2_1r][car2_1c+1] == '.') {
                score_p2++;
           }
           grid[car2_1r][car2_1c+1]='D';

           car2_1c++;
       }
    }
}


void move_ghost(ghost gh)
{
  while(1){
    int n, moveTo;
    char str1[4];
    char str[4][6];
    srand(time(0));

    if(grid[gh.r - 1][gh.c] == ' '){
        n = strlen(str1);
        str1[n] = 'v';
        strcpy(str[n],"UP");
    }
    if(grid[gh.r + 1][gh.c] == ' '){
        n = strlen(str1);
        str1[n] = 'v';
        strcpy(str[n],"DOWN");
    }
    if(grid[gh.r][gh.c + 1] == ' '){
        n = strlen(str1);
        str1[n] = 'v';
        strcpy(str[n],"RIGHT");
    }
    if(grid[gh.r][gh.c - 1] == ' '){
        n = strlen(str1);
        str1[n] = 'v';
        strcpy(str[n],"LEFT");
    }

    moveTo = rand() % strlen(str1);


    if(strcmp(str[moveTo], "UP") == 0){
      if(grid[gh.r][gh.c] != '*'){
        switch (grid[gh.r][gh.c]){
          case 'D':
            // kill('D');
            break;
          case '@':
            // kill('@');
            break;
          default:
            break;
        }

        switch (grid[gh.r][gh.c]){
          case ' ':
            grid[gh.r][gh.c] = ' ';
            grid[gh.r - 1][gh.c] = 'G';
            break;
          case '.':
            grid[gh.r][gh.c] = '.';
            grid[gh.r - 1][gh.c] = 'G';
            break;
          default:
            break;
        }
      }
    }
    else if(strcmp(str[moveTo], "DOWN") == 0){
      if(grid[gh.r][gh.c] != '*'){
        switch (grid[gh.r][gh.c]){
          case 'D':
            // kill('D');
            break;
          case '@':
            // kill('@');
            break;
          default:
            break;
        }
        switch (grid[gh.r][gh.c]){
          case ' ':
            grid[gh.r][gh.c] = ' ';
            break;
          case '.':
            grid[gh.r][gh.c] = '.';
            break;
          default:
            break;
        }
        grid[gh.r + 1][gh.c] = 'G';
      }
    }
    else if(strcmp(str[moveTo], "RIGHT") == 0){
      if(grid[gh.r][gh.c] != '*'){
        switch (grid[gh.r][gh.c]){
          case 'D':
            // kill('D');
            break;
          case '@':
            // kill('@');
            break;
          default:
            break;
        }
        switch (grid[gh.r][gh.c]){
          case ' ':
            grid[gh.r][gh.c] = ' ';
            break;
          case '.':
            grid[gh.r][gh.c] = '.';
            break;
          default:
            break;
        }

        grid[gh.r][gh.c + 1] = 'G';
      }
    }
    else if(strcmp(str[moveTo], "LEFT") == 0){
      if(grid[gh.r][gh.c] != '*'){
        switch (grid[gh.r][gh.c]){
          case 'D':
            // kill('D');
            break;
          case '@':
            // kill('@');
            break;
          default:
            break;
        }
        switch (grid[gh.r][gh.c]){
          case ' ':
            grid[gh.r][gh.c] = ' ';
            break;
          case '.':
            grid[gh.r][gh.c] = '.';
            break;
          default:
            break;
        }

        grid[gh.r][gh.c - 1] = 'G';
      }
    }
  }
}