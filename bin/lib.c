#include "lib.h"

void start_screen(){
  wborder(win, '*', '*', '*', '*', '*', '*', '*', '*');

  wattron(win, COLOR_PAIR(1));
  mvwprintw(win, 3, 1, "#######   #####   ##   ##  ##    ##  ###     ###   #####   ###     ##");
  mvwprintw(win, 4, 1, "##   ##  ##   ##  ##  ##   ##    ##  ####   ####  ##   ##  ####    ##");
  mvwprintw(win, 5, 1, "######   ##   ##  ## ##    ##    ##  ## ## ## ##  ##   ##  ## ##   ##");
  mvwprintw(win, 6, 1, "##       #######  ###      ##    ##  ##  ##   ##  #######  ##  ##  ##");
  mvwprintw(win, 7, 1, "##       ##   ##  ## ##    ##    ##  ##       ##  ##   ##  ##   ## ##");
  mvwprintw(win, 8, 1, "##       ##   ##  ##  ##   ##    ##  ##       ##  ##   ##  ##    ####");
  mvwprintw(win, 9, 1, "##       ##   ##  ##   ##  ########  ##       ##  ##   ##  ##     ###");
  wattroff(win, COLOR_PAIR(1));

  char a[30] = "=============================";
  char b[30] = "          Main Menu";
  char c[30] = "=============================";
	char choices[2][20] = {"Play", "Exit"};
  int selected = 0;
  int choice;

  mvwprintw(win, 12, max_col/2 - strlen(a)/2, "%s", a);
  mvwprintw(win, 13, max_col/2 - strlen(a)/2, "%s", b);
  mvwprintw(win, 14, max_col/2 - strlen(a)/2, "%s", c);

  while(1){
    for(int i = 0; i < 2; i++){
      if(i == selected){
        wattron(win, A_REVERSE);
      }
      mvwprintw(win, 15 + i, max_col/2 - strlen(choices[i])/2, "%s", choices[i]);
      wattroff(win, A_REVERSE);
    }

    choice = wgetch(win);
    
    if(choice == KEY_UP){
      selected = 0;
    }
    else if(choice == KEY_DOWN){
      selected = 1;
    }

    if(choice == 10){
      break;
    }
    wrefresh(win);
  }

  if(selected == 1){
    terminate_ncurses();
    exit(0);
  }

  char choices2[2][10] = {"Map 1", "Map 2"};
  selected = 0;

  mvwprintw(win, 13, max_col/2 - strlen(a)/2, "          Select Map");

  while(1){
    for(int i = 0; i < 2; i++){
      if(i == selected){
        wattron(win, A_REVERSE);
      }
      mvwprintw(win, 15 + i, max_col/2 - strlen(choices2[i])/2, "%s", choices2[i]);
      wattroff(win, A_REVERSE);
    }

    choice = wgetch(win);
    
    if(choice == KEY_UP){
      selected = 0;
    }
    else if(choice == KEY_DOWN){
      selected = 1;
    }

    if(choice == 10){
      break;
    }
    wrefresh(win);
  }

  map = selected;

  wclear(win);
  wrefresh(win);
}

void load_map(){
  switch(map){
    case 0:
          load_map_1();
          full_score = 700;
          break;
    case 1:
          load_map_2();
          full_score = 540;
          break;
    default:
          load_map_1();
          full_score = 700;
          break;
  }
  
  for(int i = 0; i < ROW; i++){
    wattron(win, COLOR_PAIR(2));
    wprintw(win, "%s\n", grid[i]);
    wattroff(win, COLOR_PAIR(2));
  }
  
  mvwprintw(stdscr, ROW, window_col/2 - 12, "Press X to stop playing");
  refresh();

  food();
  wrefresh(win);
}

void init_car(Player *car, int r, int c, char ch){
  car->r = r;
  car->c = c;
  car->ch = ch;
  car->dir = STOP;
  car->score = 0;
  car->death = 0;
  wmove(win, car->r, car->c);
  waddch(win, car->ch);
}

void init_ghost(){
  int row[5] = {14, 11, 18, 22, 27};
  int col[5] = {1, 37, 37, 3, 20};
  int row2[5] = {9, 5, 18, 25, 27};
  int col2[5] = {16, 52, 47, 69, 20};

  for(int i = 0; i < 5; i++){
    if(map == 0){
      ghosts[i].r = row[i];
      ghosts[i].c = col[i];
    }
    else{
      ghosts[i].r = row2[i];
      ghosts[i].c = col2[i];
    }

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

void *special_food(void *vargp){
  int point_col[750];
  int point_row[750];
  int k = 0, i = 0, n;
  int *random_n;
  char c_temp;

  pthread_mutex_lock(&lock);
  for(int i = 0; i < ROW -1; i++){
    for(int j = 0; j < COL -1; j++){
      char c = mvwinch(win, i, j);

      if(c == ' ' || c == '.'){
        point_row[k] = i;
        point_col[k] = j;
        k++;
      }
    }  
  }

  pthread_mutex_unlock(&lock);
  random_n = rand_number(k);

  while(isStop == 0){
    n = *(random_n + i);
    c_temp = mvwinch(win, point_row[n], point_col[n]);

    //
    mvwprintw(win, point_row[n], point_col[n], "+");
    sleep(15);

    //
    mvwprintw(win, point_row[n], point_col[n], "%c", c_temp);
    sleep(60);

    i++;
  }
}

void *user_input(void *vargp){
  int ch;

  while(isStop == 0){
    
    if(ch = getch()){

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
      else if(ch == 'x' || ch == 'X'){
        end_game();
      }
    }

  }
  pthread_exit(NULL); 
}

void kill_player(Player *car){
  car->death = 1;

  if(car1.death == 1 && car2.death == 1){
    end_game();
  }
}

int * rand_number(int limit){
  pthread_mutex_lock(&lock);
  static int numbers[100];
  
  unsigned short seed2[3] = {1, 2, 5};
  unsigned short seed[3] = {1, 9, 15};
  for(int i = 0; i < 100; i++){
    if(map == 0){
      numbers[i] = (nrand48(seed) % limit);
    }
    else{
      numbers[i] = (nrand48(seed) % limit);
    }
  }
  pthread_mutex_unlock(&lock);
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
    mvwprintw(win, 0, max_col - 15, "Score P2: %d", car.score);
  }

  if(car1.score + car2.score == full_score){
    isStop == 1;
  }
}

void *move_car1(void *vargp){
  char c = '@';
  char next_c;

  while(isStop == 0 && car1.death == 0){
    pthread_mutex_lock(&lock);
    if(car1.dir == UP){
      next_c = mvwinch(win, car1.r - 1, car1.c);

      if((next_c != '*') && (next_c != c) && (next_c != 'G')){
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
      next_c = mvwinch(win, car1.r + 1, car1.c);

      if((next_c != '*') && (next_c != c) && (next_c != 'G')){
        wmove(win, car1.r, car1.c);
        waddch(win, ' ');
        car1.r += 1;

        if(car1.r == max_row - 1){
          car1.r = 2;
        }

        if(next_c == '.'){
          car1.score++;
        }

        wmove(win, car1.r, car1.c);
        waddch(win, car1.ch);
      }
    }
    if(car1.dir == LEFT){
      next_c = mvwinch(win, car1.r, car1.c - 1);

      if((next_c != '*') && (next_c != c) && (next_c != 'G')){
        wmove(win, car1.r, car1.c);
        waddch(win, ' ');
        car1.c -= 1;

        if(car1.c == 0){
          car1.c = 1;
        }

        if(next_c == '.'){
          car1.score++;
        }
        wmove(win, car1.r, car1.c);
        waddch(win, car1.ch);
      }
    }
    else if(car1.dir == RIGHT){
      next_c = mvwinch(win, car1.r, car1.c  + 1);

      if((next_c != '*') && (next_c != c) && (next_c != 'G')){
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

    if(next_c == '+') {
      car2.score -= 10;
    }

    show_score(car1);
    wrefresh(win);
    pthread_mutex_unlock(&lock);
    delayOn();
  }

  if(car1.death == 1){
    car1.dir = STOP;
    wmove(win, car1.r, car1.c);
    waddch(win, ' ');
    wrefresh(win);
  }
  return NULL;
}

void *move_car2(void *vargp){
  char c = 'C';
  char next_c;

  while(isStop == 0 && car2.death == 0){
    pthread_mutex_lock(&lock);
    if(car2.dir == UP){
      next_c = mvwinch(win, car2.r - 1, car2.c);

      if((next_c != '*') && (next_c != c) && (next_c != 'G')){
        wmove(win, car2.r, car2.c);
        waddch(win, ' ');
        car2.r -= 1;

        if(car2.r == beg_row){
          car2.r = beg_row + 1;
        }

        if(next_c == '.') {
          car2.score++;
        }
        wmove(win, car2.r, car2.c);
        waddch(win, car2.ch);
      }
    }
    else if(car2.dir == DOWN){
      next_c = mvwinch(win, car2.r + 1, car2.c);

      if((next_c != '*') && (next_c != c) && (next_c != 'G')){
        wmove(win, car2.r, car2.c);
        waddch(win, ' ');
        car2.r += 1;

        if(car2.r == max_row - 1){
          car2.r = 2;
        }

        if(next_c == '.'){
          car2.score++;
        }
        wmove(win, car2.r, car2.c);
        waddch(win, car2.ch);
      }
    }
    if(car2.dir == LEFT){
      next_c = mvwinch(win, car2.r, car2.c - 1);

      if((next_c != '*') && (next_c != c) && (next_c != 'G')){
        wmove(win, car2.r, car2.c);
        waddch(win, ' ');
        car2.c -= 1;
        
        if(car2.c == 0){
          car2.c = 1;
        }

        if(next_c == '.'){
          car2.score++;
        }
        wmove(win, car2.r, car2.c);
        waddch(win, car2.ch);
      }
    }
    else if(car2.dir == RIGHT){
      next_c = mvwinch(win, car2.r, car2.c  + 1);

      if((next_c != '*') && (next_c != c) && (next_c != 'G')){
        wmove(win, car2.r, car2.c);
        waddch(win, ' ');
        car2.c += 1;

        if(car2.c == max_col - 1){
          car2.c = max_col - 2;
        }
        
        if(next_c == '.'){
          car2.score++;
        }
        wmove(win, car2.r, car2.c);
        waddch(win, car2.ch);
      }
    }

    if(next_c == '+') {
      car1.score -= 10;
    }
    
    show_score(car2);
    wrefresh(win);
    pthread_mutex_unlock(&lock);
    delayOn();
  }

  if(car2.death == 1){
    car2.dir = STOP;
    wmove(win, car2.r, car2.c);
    wrefresh(win);
    waddch(win, ' ');
  }
  return NULL;
}

void *move_ghost(void *i){
  int move_to, n = 0;
  int *random_numbers;
  char next_c;
  int index = *((int *) i);
  Ghosts ghost = ghosts[index];

  random_numbers = rand_number(4);

  while(isStop == 0){
    pthread_mutex_lock(&lock);
    
    if(n == 99){
      n = 0;
    }
    
    if(ghost.dir == UP){
      next_c = mvwinch(win, ghost.r - 1, ghost.c);

      if(next_c == '*' || next_c == 'G'){
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

      if(next_c == '*' || next_c == 'G'){
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

      if(next_c == '*' || next_c == 'G'){
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

      if(next_c == '*' || next_c == 'G'){
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
    wrefresh(win);
    
    char dir[4];
    int open_dir = 0;

    dir[0] = mvwinch(win, ghost.r + 1, ghost.c);
    dir[1] = mvwinch(win, ghost.r - 1, ghost.c);
    dir[2] = mvwinch(win, ghost.r, ghost.c + 1);
    dir[3] = mvwinch(win, ghost.r, ghost.c - 1);
    
    for(int x = 0; x < 4; x++){
      if(dir[x] == '.' || dir[x] == ' '){
        open_dir++;
        if(open_dir > 2){
          ghost.dir = STOP;
        }
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

    // Kill Player
    if ((ghost.r == car1.r) && (ghost.c == car1.c)) {
      kill_player(&car1);
    }
    if ((ghost.r == car2.r) && (ghost.c == car2.c)) {
      kill_player(&car2);
    }

    n++;
    pthread_mutex_unlock(&lock);
    if(ghost.dir != STOP){
      delayOn();
    }
  }
  return NULL;
}

void ghost_footprint(Ghosts *ghost, char next_c){
  ghost->foot = next_c;
  
  if(next_c == '@' || next_c == 'C'){
    ghost->foot = ' ';
  }
}

void end_screen(){
  wclear(win);
  wborder(win, '*', '*', '*', '*', '*', '*', '*', '*');

  wattron(win, A_BLINK);
  wattron(win, COLOR_PAIR(1));
  mvwprintw(win, 3, 5, "#####   ###   ##   ##  #####    #####  #       #  #####  #####");
  mvwprintw(win, 4, 5, "#      #   #  # # # #  #        #   #   #     #   #      #   #");
  mvwprintw(win, 5, 5, "#  ##  #####  #  #  #  #####    #   #    #   #    #####  ####");
  mvwprintw(win, 6, 5, "#   #  #   #  #     #  #        #   #     # #     #      #  #");
  mvwprintw(win, 7, 5, "#####  #   #  #     #  #####    #####      #      #####  #   #");
  wattroff(win, COLOR_PAIR(1));
  wattroff(win, A_BLINK);

  wattron(win, A_BOLD);
  mvwprintw(win, 10, max_col/2 - 2, "SCORE");
  wattroff(win, A_BOLD);
  mvwprintw(win, 11, max_col/2 - 11, "=====================");
  mvwprintw(win, 12, max_col/2 - 10, "Player 1 : %d", car1.score);
  mvwprintw(win, 13, max_col/2 - 10, "Player 2 : %d", car2.score);
  mvwprintw(win, 14, max_col/2 - 11, "=====================");
  mvwprintw(win, 16, max_col/2 - 7, "PRESS ANY KEY");

  int winner;
  if (car1.score > car2.score){
    winner = 12;
  }
  else if(car1.score < car2.score){
    winner = 13;
  }

  wattron(win, A_REVERSE);
  mvwprintw(win, winner, max_col/2 + 4, " WIN ");
  wattroff(win, A_REVERSE);

  wrefresh(win);
}

void end_game(){
  isStop = 1;
  pthread_cancel(t_spcfood);
  pthread_cancel(t_input1);
}

void terminate_ncurses(){
  curs_set(1);
  clear();
  refresh();
  resetty();
  endwin();
}

void load_map_1(){
  strcpy(grid[0],  "***********************************************************************"),
  strcpy(grid[1],  "*                                                                     *"),
  strcpy(grid[2],  "* ***************** *************** *************** ***************** *"),
  strcpy(grid[3],  "* ***************** *************** *************** ***************** *"),
  strcpy(grid[4],  "* *********                 ******* *******                 ********* *"),
  strcpy(grid[5],  "* ********* ******* ******* ******* ******* ******* ******* ********* *"),
  strcpy(grid[6],  "* ********* *             * ******* ******* *             * ********* *"),
  strcpy(grid[7],  "* ********* * *********** * ****       **** * *********** * ********* *"),
  strcpy(grid[8],  "* ********* * *********** * **** ***** **** * *********** * ********* *"),
  strcpy(grid[9],  "*                                *****                                *"),
  strcpy(grid[10], "* ***************** ***** ****** ***** ****** ***** ***************** *"),
  strcpy(grid[11], "* ***************** ***** ******       ****** ***** ***************** *"),
  strcpy(grid[12], "* ***************** ***** ****** ***** ****** ***** ***************** *"),
  strcpy(grid[13], "* ***************** *****                     ***** ***************** *"),
  strcpy(grid[14], "*                         *******************                         *"),
  strcpy(grid[15], "**** ************** ***** ******************* ***** ************* *****"),
  strcpy(grid[16], "**** ************** ***** ******************* ***** ************* *****"),
  strcpy(grid[17], "*                         *******************                         *"),
  strcpy(grid[18], "* ***************** *****                     ***** ***************** *"),
  strcpy(grid[19], "* ***************** ***** ****** ***** ****** ***** ***************** *"),
  strcpy(grid[20], "* ***************** ***** ******       ****** ***** ***************** *"),
  strcpy(grid[21], "* ***************** ***** ****** ***** ****** ***** ***************** *"),
  strcpy(grid[22], "*                                *****                                *"),
  strcpy(grid[23], "* ********* * *********** * **** ***** **** * *********** * ********* *"),
  strcpy(grid[24], "* ********* * *********** * ****       **** * *********** * ********* *"),
  strcpy(grid[25], "* ********* *             * ******* ******* *             * ********* *"),
  strcpy(grid[26], "* ********* ******* ******* ******* ******* ******* ******* ********* *"),
  strcpy(grid[27], "* *********                 ******* *******                 ********* *"),
  strcpy(grid[28], "* ***************** *************** *************** ***************** *"),
  strcpy(grid[29], "* ***************** *************** *************** ***************** *"),
  strcpy(grid[30], "*                                                                     *"),
  strcpy(grid[31], "***********************************************************************");
}

void load_map_2(){
  strcpy(grid[0],  "***********************************************************************"),
  strcpy(grid[1],  "*                                 **                                  *"),
  strcpy(grid[2],  "* *************** *************** ** ******************* ************ *"),
  strcpy(grid[3],  "* *************** *************** ** ******************* ************ *"),
  strcpy(grid[4],  "* *************** *************** ** ******************* ************ *"),
  strcpy(grid[5],  "*                                                                     *"),
  strcpy(grid[6],  "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[7],  "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[8],  "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[9],  "*                 ********       ********       ******** ************ *"),
  strcpy(grid[10], "* *************** ************** ******** ************** ************ *"),
  strcpy(grid[11], "* *************** ************** ******** ************** ************ *"),
  strcpy(grid[12], "* *************** ************** ******** ************** ************ *"),
  strcpy(grid[13], "* *************** ********                      ******** ************ *"),
  strcpy(grid[14], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[15], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[16], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[17], "*                          ********************                       *"),
  strcpy(grid[18], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[19], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[20], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[21], "* *************** ********                      ******** ************ *"),
  strcpy(grid[22], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[23], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[24], "* *************** ******** ******************** ******** ************ *"),
  strcpy(grid[25], "*                                ********                             *"),
  strcpy(grid[26], "* *************** ************** ******** ************** ************ *"),
  strcpy(grid[27], "* ***************      ***       ********       ***      ************ *"),
  strcpy(grid[28], "*           ***** **** *** ***** ******** ***** *** **** ******       *"),
  strcpy(grid[29], "*********** ***** ****     ***** ******** *****     **** ****** *******"),
  strcpy(grid[30], "***********            ***                      ***             *******"),
  strcpy(grid[31], "***********************************************************************");
}