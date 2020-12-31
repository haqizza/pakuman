#include "lib.h"

void createMap(){
  strcpy(grid[0],  "***********************************************************************"),
  strcpy(grid[1],  "*G                D                                                   *"),
  strcpy(grid[2],  "*   ***************         *******   ******        ***************   *"),
  strcpy(grid[3],  "*   ***************         *******   ******        ***************   *"),
  strcpy(grid[4],  "*   ***************         *******   ******        ***************   *"),
  strcpy(grid[5],  "*   *******                 *******   ******                *******   *"),
  strcpy(grid[6],  "*   *******                 *******   ******                *******   *"),
  strcpy(grid[7],  "*   *******                 *******   ******                *******   *"),
  strcpy(grid[8],  "*   *******                 *******   ******                *******   *"),
  strcpy(grid[9],  "*                                @                                    *"),
  strcpy(grid[10], "*                   **************    **************                  *"),
  strcpy(grid[11], "*                   **************    **************                  *"),
  strcpy(grid[12], "*                   **************    **************                  *"),
  strcpy(grid[13], "*                   **************    **************                  *"),
  strcpy(grid[14], "*                   **************    **************                  *"),
  strcpy(grid[15], "*     ****************************    ******************************  *"),
  strcpy(grid[16], "*     ****************************    ******************************  *"),
  strcpy(grid[17], "*     ****************************    ******************************  *"),
  strcpy(grid[18], "*     ****************************    ******************************  *"),
  strcpy(grid[19], "*                                                                     *"),
  strcpy(grid[20], "*                                                                     *"),
  strcpy(grid[21], "*                                                                     *"),
  strcpy(grid[22], "*                                                                     *"),
  strcpy(grid[23], "*    **********************                 **********************    *"),
  strcpy(grid[24], "*    **********************                 **********************    *"),
  strcpy(grid[25], "*    **********************                 **********************    *"),
  strcpy(grid[26], "*    ***********                                       ***********    *"),
  strcpy(grid[27], "*    ***********                                       ***********    *"),
  strcpy(grid[28], "*    ***********                                       ***********    *"),
  strcpy(grid[29], "*                                                                     *"),
  strcpy(grid[30], "*                                                                     *"),
  strcpy(grid[31], "***********************************************************************");
}

void init_ghost(ghost *gh,int row, int col){
  (*gh).r = row;
  (*gh).c = col;
}

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


void score() {
    if(grid[car_1r][car_1c] == '.') {
        score_p1++;
    } 
    if(grid[car2_1r][car2_1c] == '.') {
        score_p2++;
    }
}

void delay(){
    int delay_i, delay_j;
    for(delay_i=0;delay_i<4000;delay_i++) {
        for(delay_j=0;delay_j<10000;delay_j++) {}
    } 
}

void print_grid(){
    int i;

    for(i=0;i<ROW;i++)
    printf("%s\n",grid[i]);

    printf("\nScore P1: %d\n", score_p1);
    printf("Score P2: %d\n", score_p2);
    printf("(X,Y) P1 : (%d,%d)\n", car_1r, car_1c);
    printf("(X,Y) P2 : (%d,%d)\n", car2_1r, car2_1c);

}
void move_car(moves dir){
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

void move_car2(moves dir){
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

void move_ghost(ghost *gh){
  int n, moveTo;
  char str1[4];
  char str[4][6];
  srand(time(0));

  if(grid[(*gh).r - 1][(*gh).c] != '*'){
      n = strlen(str1);
      str1[n] = 'v';
      strcpy(str[n],"UP");
  }
  if(grid[(*gh).r + 1][(*gh).c] != '*'){
      n = strlen(str1);
      str1[n] = 'v';
      strcpy(str[n],"DOWN");
  }
  if(grid[(*gh).r][(*gh).c + 1] != '*'){
      n = strlen(str1);
      str1[n] = 'v';
      strcpy(str[n],"RIGHT");
  }
  if(grid[(*gh).r][(*gh).c - 1] != '*'){
      n = strlen(str1);
      str1[n] = 'v';
      strcpy(str[n],"LEFT");
  }
  
  moveTo = rand() % strlen(str1);
  // (*gh).c = moveTo;

  if(strcmp(str[moveTo], "UP") == 0){
    // switch (grid[(*gh).r][(*gh).c]){
    //   case 'D':
    //     // kill('D');
    //     break;
    //   case '@':
    //     // kill('@');
    //     break;
    //   default:
    //     break;
    // }
    switch (grid[(*gh).r][(*gh).c]){
      case ' ':
        grid[(*gh).r][(*gh).c] = ' ';
        break;
      case '.':
        grid[(*gh).r][(*gh).c] = '.';
        break;
      default:
        break;
    }
    grid[(*gh).r - 1][(*gh).c] = 'G';
  }
  else if(strcmp(str[moveTo], "DOWN") == 0){
    // (*gh).r++;
    // switch (grid[(*gh).r][(*gh).c]){
    //   case 'D':
    //     // kill('D');
    //     break;
    //   case '@':
    //     // kill('@');
    //     break;
    //   default:
    //     break;
    // }
    switch (grid[(*gh).r][(*gh).c]){
      case ' ':
        grid[(*gh).r][(*gh).c] = ' ';
        break;
      case '.':
        grid[(*gh).r][(*gh).c] = '.';
        break;
      default:
        break;
    }
    grid[(*gh).r + 1][(*gh).c] = 'G';
  }
  else if(strcmp(str[moveTo], "RIGHT") == 0){
    // switch (grid[(*gh).r][(*gh).c]){
    //   case 'D':
    //     // kill('D');
    //     break;
    //   case '@':
    //     // kill('@');
    //     break;
    //   default:
    //     break;
    // }
    switch (grid[(*gh).r][(*gh).c]){
      case ' ':
        grid[(*gh).r][(*gh).c] = ' ';
        break;
      case '.':
        grid[(*gh).r][(*gh).c] = '.';
        break;
      default:
        break;
    }

    grid[(*gh).r][(*gh).c + 1] = 'G';
  }
  else if(strcmp(str[moveTo], "LEFT") == 0){
    // switch (grid[(*gh).r][(*gh).c]){
    //   case 'D':
    //     // kill('D');
    //     break;
    //   case '@':
    //     // kill('@');
    //     break;
    //   default:
    //     break;
    // }
    switch (grid[(*gh).r][(*gh).c]){
      case ' ':
        grid[(*gh).r][(*gh).c] = ' ';
        break;
      case '.':
        grid[(*gh).r][(*gh).c] = '.';
        break;
      default:
        break;
    }

    grid[(*gh).r][(*gh).c - 1] = 'G';
  }
}