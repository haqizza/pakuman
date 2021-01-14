#include "lib.h"

int main(){
  pthread_t t_car1, t_car2;
  pthread_t t_ghost[GHOST_NUMBER];
  int i;

  // ncurses Init
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);

  getmaxyx(stdscr, window_row, window_col);
  
  if(window_row < ROW || window_col < COL){
    printw("Jendela terlalu kecil, perbesar\n");
  }

  // Window Setup
  win = newwin(ROW, COL, 0, window_col/2 - COL/2);
  keypad(win, TRUE);
  keypad(stdscr, TRUE);
  getmaxyx(win, max_row, max_col);
  getbegyx(win, beg_row, beg_col);
  refresh();

  // Check Color
  if(!has_colors()){
    mvwprintw(win, 3, max_col/2 - COL/2, "Your terminal doesn't have color");
    getch();
  }

  // Start Color
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLUE);
  
  while(1){
    wrefresh(win);
    start_screen();
    load_map();

    isStop = 0;
    
    // Init Player
    init_car(&car1, 1, 1, 'C');
    init_car(&car2, 1, 69, '@');
    // Init Ghost
    init_ghost();
    
    // Threads
    pthread_create(&t_input1, NULL, user_input, NULL);
    pthread_create(&t_car1, NULL, move_car1, NULL);
    pthread_create(&t_car2, NULL, move_car2, NULL);
    pthread_create(&t_spcfood, NULL, special_food, NULL);

    for (i = 0; i < GHOST_NUMBER; i++) {
      int *arg = malloc(sizeof(*arg));
      *arg = i;
      pthread_create(&t_ghost[i], NULL, move_ghost, arg);
    }

    pthread_join(t_car1, NULL);
    pthread_join(t_car2, NULL);
    
    for (i = 0; i < GHOST_NUMBER; i++) {
      pthread_join(t_ghost[i], NULL);
    }
    pthread_join(t_input1, NULL);
    pthread_join(t_spcfood, NULL);

    wrefresh(win);
    clear();
    refresh();
    end_screen();
    getch();
    wclear(win);
  }

  terminate_ncurses();
  return 0;
}
