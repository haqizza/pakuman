#include "lib.h"

int main(){
  pthread_t t_car1, t_car2;
  pthread_t t_input1, t_input2;
  pthread_t t_ghost[5];

  // Init ncurses
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);

  getmaxyx(stdscr, max_row, max_col);
  if(max_row < ROW || max_col < COL){
    printw("Jendela terlalu kecil, perbesar\n");
  }

  win = newwin(ROW, COL, 0, max_col/2 - COL/2);
  keypad(win, TRUE);
  getmaxyx(win, max_row, max_col);
  getbegyx(win, beg_row, beg_col);
  refresh();

  loadMap();

  isStop = 0;
  
  // Init Player
  init_car(&car1, 1, 1, 'C');
  init_car(&car2, 1, 69, '@');
  // Init Ghost
  init_ghost();

  wrefresh(win);

  pthread_create(&t_input1, NULL, userInput, NULL);
  pthread_create(&t_car1, NULL, move_car1, NULL);
  pthread_create(&t_car2, NULL, move_car2, NULL);

  int i;
  for (i = 0; i < GHOST_NUMBER; i++) {
    int *arg = malloc(sizeof(*arg));
    *arg = i;
	  pthread_create(&t_ghost[i], NULL, move_ghost, arg);
  }

  pthread_join(t_input1, NULL);
  pthread_join(t_car1, NULL);
  pthread_join(t_car2, NULL);
  
  for (i = 0; i < GHOST_NUMBER; i++) {
	  pthread_join(t_ghost[i], NULL);
  }

  end_screen();
  
  curs_set(1);
  clear();
  refresh();
  resetty();
  endwin();
  return 0;
}
