#include "lib.h"

int main(){
  createMap();

  direction = STOP;
  direction2 = STOP;
  int i, count = 1;

  ghost ghost1;
  init_ghost(&ghost1, 1, 1);

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
    // move_ghost(&ghost1);
    system("cls");
    print_grid();
    delay();
  }
  return 0;
}