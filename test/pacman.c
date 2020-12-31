#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>

#define ROW 32
#define COL 72

// typedef enum{
//     UP,
//     DOWN,
//     LEFT,
//     RIGHT,
//     STOP
// } move;

// typedef struct{
    
// } ghost;


enum move {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
} direction, direction2, gh1_dir;



void move_car(enum move dir);
void move_car2(enum move dir);

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

  gh_1r = 2;
  gh_1c = 2;

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
    move_ghost(gh1_dir);
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
void move_car(enum move dir)
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

void move_car2(enum move dir)
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

void move_ghost(enum move dir)
{
    int n;
    char str[4][6];
    srand(time(0));

    if(grid[gh_1r - 1][gh_1c]){
        n = strlen(str);
        strcpy(str[n],"UP");
    }
    if(grid[gh_1r + 1][gh_1c]){
        n = strlen(str);
        strcpy(str[n],"DOWN");
    }
    if(grid[gh_1r][gh_1c + 1]){
        n = strlen(str);
        strcpy(str[n],"RIGHT");
    }
    if(grid[gh_1r][gh_1c - 1]){
        n = strlen(str);
        strcpy(str[n],"LEFT");
    }
    rand();


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