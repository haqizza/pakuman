#include ".\lib\config.h"
#include ".\lib\maps.h"

int main()
{
  direction = STOP;
  direction2 = STOP;
  // ghost1_dir = STOP1;
  // ghost2_dir = STOP1;
  int i,count=20;
  car_1r = 8;
  car_1c =33;
  car_2r = 8;
  car_2c = 34;
  car2_1r = 1;
  car2_1c =18;
  car2_2r = 1;
  car2_2c = 19;
  // ghost1_r=1;
  // ghost1_c=43;
  // ghost2_r=19;
  // ghost2_c=18;
  char ch;
  print_grid();
  // ghost1_direction();
  // ghost2_direction();

  while(count)
  {
    if(_kbhit()){
      ch=_getch();
      switch(ch)
      {
        case 'd':
                direction = RIGHT;
                break;
        case 'a':
                direction = LEFT;
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

    // if(grid[ghost1_r][ghost1_c]==grid[car_1r][car_1c]||grid[ghost1_r][ghost1_c]==grid[car_2r][car_2c])
    // {
    //     printf("\nGAME OVER\n");
    //     break;
    // }
    move_car(direction);
    move_car2(direction2);
  // ghost_direction();
    // ghost1_move(ghost1_dir);

    // ghost2_move(ghost2_dir);
    Beep(400,150);
    system("cls");
    print_grid();
  }
return 0;
}

