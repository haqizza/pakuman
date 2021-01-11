#include "lib.h"

void loadMap(){
  strcpy(grid[0],  "***********************************************************************"),
  strcpy(grid[1],  "*                                                                     *"),
  strcpy(grid[2],  "*   ***************         *******   ******        ***************   *"),
  strcpy(grid[3],  "*   ***************         *******   ******        ***************   *"),
  strcpy(grid[4],  "*   ***************         *******   ******        ***************   *"),
  strcpy(grid[5],  "*   *******                 *******   ******                *******   *"),
  strcpy(grid[6],  "*   *******                 *******   ******                *******   *"),
  strcpy(grid[7],  "*   *******                 *******   ******                *******   *"),
  strcpy(grid[8],  "*   *******                 *******   ******                *******   *"),
  strcpy(grid[9],  "*                                                                     *"),
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

  for(int i = 0; i < ROW; i++){
    wprintw(win, "%s\n", grid[i]);
  }
  food();
  wrefresh(win);
}

void init_car(Player *car, int r, int c, char ch){
  car->r = r;
  car->c = c;
  car->ch = ch;
  car->dir = STOP;
  car->score = 0;
  wmove(win, car->r, car->c);
  waddch(win, car->ch);
}

void init_ghost(){
  int row[5] = {9, 9, 19, 22, 27};
  int col[5] = {1, 60, 40, 3, 20};

  for(int i = 0; i < 5; i++){
    ghosts[i].r = row[i];
    ghosts[i].c = col[i];
    ghosts[i].foot = '.';
    wmove(win, ghosts[i].r, ghosts[i].c);
    waddch(win, 'G');
  }
}

void food() {
  int x, y;

  for(y = 0; y < ROW; y++) {    
    for(x = 1; x < COL - 1; x++) {
      wmove(win, y, x);
      if(grid[y][x] == ' '){
        waddch(win, '.');
      }
    }
  }
}

void *user1Input(void *arg){
  int ch;
  while(isStop == 0){
    if(ch = wgetch(win)){
      if(ch == 'd'){
        car1.dir = RIGHT;
      }
      else if(ch == 'a'){
        car1.dir = LEFT;
      }
      else if(ch == 'w'){
        car1.dir = UP;
      }
      else if(ch == 's'){
        car1.dir = DOWN;
      }
      else if(ch == KEY_RIGHT){
        car2.dir = RIGHT;
      }
      else if(ch == KEY_LEFT){
        car2.dir = LEFT;
      }
      else if(ch == KEY_UP){
        car2.dir = UP;
      }
      else if(ch == KEY_DOWN){
        car2.dir = DOWN;
      }
    }
  }
}

void *user2Input(void *arg){
  int ch;
  while(isStop == 0){
    if(ch = wgetch(win)){
      if(ch == KEY_RIGHT){
        car2.dir = RIGHT;
      }
      else if(ch == KEY_LEFT){
        car2.dir = LEFT;
      }
      else if(ch == KEY_UP){
        car2.dir = UP;
      }
      else if(ch == KEY_DOWN){
        car2.dir = DOWN;
      }
    }
  }
}

void kill(Player *car){

}

int * randNumber(){
  static int numbers[100];
  struct timeval t;
  srand(time(0));
  int n;
  unsigned short seed[3] = {1, 2, 5};
  for(int i = 0; i < 100; i++){
    numbers[i] = (nrand48(seed) % 4);
  }

  return numbers;
}

void delayOn(){
  struct timespec t, t2;
	t.tv_sec  = 0;
  t.tv_nsec = 300000000L;
  nanosleep(&t, &t2);
}

void show_score(Player car){
  if(car.ch == 'C'){
    mvwprintw(win, 0, 1, "Score P1: %d", car.score);
  }
  else{
    mvwprintw(win, 0, max_col - 13, "Score P2: %d", car.score);
  }
}

void *move_car1(void *arg){
  char c = '@';

  while(isStop == 0){
    pthread_mutex_lock(&lock);
    if(car1.dir == UP){
      char next_c = mvwinch(win, car1.r - 1, car1.c);

      if((next_c != '*') && (next_c != c)){
        wmove(win, car1.r, car1.c);
        waddch(win, ' ');
        car1.r -= 1;

        if(car1.r == beg_row){
          car1.r = beg_row + 1;
        }

        if(next_c == '.') {
          car1.score++;
        }

        wmove(win, car1.r, car1.c);
        waddch(win, car1.ch);
      }
    }
    else if(car1.dir == DOWN){
      char next_c = mvwinch(win, car1.r + 1, car1.c);

      if((next_c != '*') && (next_c != c)){
        wmove(win, car1.r, car1.c);
        waddch(win, ' ');
        car1.r += 1;

        if(car1.r == max_row - 1){
          car1.r = max_row - 2;
        }

        if(next_c == '.'){
          car1.score++;
        }

        wmove(win, car1.r, car1.c);
        waddch(win, car1.ch);
      }
    }
    if(car1.dir == LEFT){
      char next_c = mvwinch(win, car1.r, car1.c - 1);

      if((next_c != '*') && (next_c != c)){
        wmove(win, car1.r, car1.c);
        waddch(win, ' ');
        car1.c -= 1;

        if(car1.c == beg_col){
          car1.c = beg_col + 1;
        }

        if(next_c == '.'){
          car1.score++;
        }
        wmove(win, car1.r, car1.c);
        waddch(win, car1.ch);
      }
    }
    else if(car1.dir == RIGHT){
      char next_c = mvwinch(win, car1.r, car1.c  + 1);

      if((next_c != '*') && (next_c != c)){
        wmove(win, car1.r, car1.c);
        waddch(win, ' ');
        car1.c += 1;

        if(car1.c == max_col - 1){
          car1.c = max_col - 2;
        }

        if(next_c == '.'){
          car1.score++;
        }
        wmove(win, car1.r, car1.c);
        waddch(win, car1.ch);
      }
    }

    show_score(car1);
    wrefresh(win);
    pthread_mutex_unlock(&lock);
    delayOn();
  }
}

void *move_car2(void *arg){
  char c = 'C';

  while(isStop == 0){
    pthread_mutex_lock(&lock);
    if(car2.dir == UP){
      char next_c = mvwinch(win, car2.r - 1, car2.c);

      if((next_c != '*') && (next_c != c)){
        wmove(win, car2.r, car2.c);
        waddch(win, ' ');
        car2.r -= 1;

        if(next_c == '.') {
          car2.score++;
        }
        wmove(win, car2.r, car2.c);
        waddch(win, car2.ch);
      }
    }
    else if(car2.dir == DOWN){
      char next_c = mvwinch(win, car2.r + 1, car2.c);

      if((next_c != '*') && (next_c != c)){
        wmove(win, car2.r, car2.c);
        waddch(win, ' ');
        car2.r += 1;

        if(next_c == '.'){
          car2.score++;
        }
        wmove(win, car2.r, car2.c);
        waddch(win, car2.ch);
      }
    }
    if(car2.dir == LEFT){
      char next_c = mvwinch(win, car2.r, car2.c - 1);

      if((next_c != '*') && (next_c != c)){
        wmove(win, car2.r, car2.c);
        waddch(win, ' ');
        car2.c -= 1;

        if(next_c == '.'){
          car2.score++;
        }
        wmove(win, car2.r, car2.c);
        waddch(win, car2.ch);
      }
    }
    else if(car2.dir == RIGHT){
      char next_c = mvwinch(win, car2.r, car2.c  + 1);

      if((next_c != '*') && (next_c != c)){
        wmove(win, car2.r, car2.c);
        waddch(win, ' ');
        car2.c += 1;

        if(next_c == '.'){
          car2.score++;
        }
        wmove(win, car2.r, car2.c);
        waddch(win, car2.ch);
      }
    }
    
    show_score(car2);
    wrefresh(win);
    pthread_mutex_unlock(&lock);
    delayOn();
  }
}

void *move_ghost(void *i){
  int move_to, n = 0;
  int *random_numbers;
  char next_c;
  int index = *((int *) i);
  Ghosts ghost = ghosts[index];

  random_numbers = randNumber();

  while(isStop == 0){
    pthread_mutex_lock(&lock);
    
    if(n == 99){
      n = 0;
    }
    
    if(ghost.dir == UP){
      next_c = mvwinch(win, ghost.r - 1, ghost.c);

      if(next_c == '*'){
        ghost.dir = STOP;
      }
      else{

        ghost_footprint(&ghost, next_c);
        wmove(win, ghost.r, ghost.c);
        waddch(win, ghost.foot);
        ghost.r -= 1;

        if(ghost.r == 0){
          ghost.r = 1;
          ghost.dir = STOP;
        }

        if(ghost.r == beg_row){
          ghost.r = beg_row + 1;
        }

        wmove(win, ghost.r, ghost.c);
        waddch(win, 'G');
      }
    }
    else if(ghost.dir == DOWN){
      next_c = mvwinch(win, ghost.r + 1, ghost.c);

      if(next_c == '*'){
        ghost.dir = STOP;
      }
      else{
        ghost_footprint(&ghost, next_c);
        wmove(win, ghost.r, ghost.c);
        waddch(win, ghost.foot);
        ghost.r += 1;

        if(ghost.r == max_row - 1){
          ghost.r = max_row - 2;
          ghost.dir = STOP;
        }

        wmove(win, ghost.r, ghost.c);
        waddch(win, 'G');
      }
    }
    else if(ghost.dir == RIGHT){
      next_c = mvwinch(win, ghost.r, ghost.c + 1);

      if(next_c == '*'){
        ghost.dir = STOP;
      }
      else{
        ghost_footprint(&ghost, next_c);
        wmove(win, ghost.r, ghost.c);
        waddch(win, ghost.foot);
        ghost.c += 1;

        if(ghost.c == max_col - 1){
          ghost.c = max_col - 2;
          ghost.dir = STOP;
        }

        wmove(win, ghost.r, ghost.c);
        waddch(win, 'G');
      }
    }
    else if(ghost.dir == LEFT){
      next_c = mvwinch(win, ghost.r, ghost.c - 1);

      if(next_c == '*'){
        ghost.dir = STOP;
      }
      else{
        ghost_footprint(&ghost, next_c);
        wmove(win, ghost.r, ghost.c);
        waddch(win, ghost.foot);
        ghost.c -= 1;

        if(ghost.c == beg_col){
          ghost.c = beg_col + 1;
          ghost.dir = STOP;
        }

        wmove(win, ghost.r, ghost.c);
        waddch(win, 'G');
      }
    }

    move_to = *(random_numbers + n);

    if(ghost.dir == STOP){
      switch(move_to){
        case 0:
              ghost.dir = UP;
              break;
        case 1:
              ghost.dir = DOWN;
              break;
        case 2:
              ghost.dir = RIGHT;
              break;
        case 3:
              ghost.dir = LEFT;
              break;
        default:
              break;
      }
    }

    if ((ghost.r == car1.r) && (ghost.c == car1.c)) {
      kill(&car1);
    }
    if ((ghost.r == car2.r) && (ghost.c == car2.c)) {
      kill(&car2);
    }

    n++;
    
    wrefresh(win);
    refresh();
    pthread_mutex_unlock(&lock);
    if(ghost.dir != STOP){
      delayOn();
    }
  }
}

void ghost_footprint(Ghosts *ghost, char next_c){
  if(next_c == '.'){
    ghost->foot = '.';
  }
  else if(next_c == ' '){
    ghost->foot = ' ';
  }
}