#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>

#define ROW 21
#define COL 72


enum move {UP,DOWN,LEFT,RIGHT,STOP}direction, direction2;
//enum move2 {UP2,DOWN2,LEFT2,RIGHT2,STOP2}direction2;
//enum ghost_move {UP1,DOWN1,LEFT1,RIGHT1,STOP1} ghost1_dir,ghost2_dir;
//enum move ghost1_dir,ghost2_dir;

void move_car(enum move dir);
void move_car2(enum move dir);
// void ghost1_direction();
// void ghost2_direction();
// void ghost1_move(enum ghost_move g1_dir);
// void ghost2_move(enum ghost_move g2_dir);

int car_1r,car_1c,car_2r,car_2c;
int car2_1r,car2_1c,car2_2r,car2_2c;
// int ghost1_r, ghost1_c;
// int ghost2_r,ghost2_c,ghost11,ghost22;


char grid[ROW][COL]= {
"***********************************************************************",
"*                 ;;                                                  *",
"*   ********   *********   ***************   ********************     *",
"*   *      *   *       *   *             *   *                  *     *",
"*   *      *   *       *   *             *   *                  *     *",
"*   *      *   *       *   *             *   *                  *     *",
"*   *      *   *       *   *             *   *                  *     *",
"*   ********   *********   ***************   ********************     *",
"*                                ::                                   *",
"*   ****************************   ******************************     *",
"*   *                          *   *                            *     *",
"*   *                          *   *                            *     *",
"*   *                          *   *                            *     *",
"*   *                          *   *                            *     *",
"*   *                          *   *                            *     *",
"*   *                          *   *                            *     *",
"*   *                          *   *                            *     *",
"*   *                          *   *                            *     *",
"*   ****************************   ******************************     *",
"*                                                                     *",
"***********************************************************************"};

void print_grid();

int main()
{
direction= STOP;
direction2= STOP;
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
    // if(_kbhit()){

    //    ch=_getch();
    //  switch(ch)
    //   {
    //     case 'l':

    //             direction2=RIGHT;
    //             break;


    //     case 'j':

    //             direction2=LEFT;
    //             break;


    //     case 'i':

    //             direction2 = UP;
    //             break;


    //     case 'k':

    //             direction2 = DOWN;
    //             break;


    //     default:;

    //   }
    // }

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

void print_grid()
{
    int i;

    for(i=0;i<ROW;i++)
    printf("%s\n",grid[i]);

    // printf("\ng2:%d dir: %d\n",ghost22,ghost2_dir);

    // printf("\ng2:%d g2:%d\n",ghost2_r,ghost2_c);

}
void move_car(enum move dir)
{
    if(dir==UP)
    {
        if(grid[car_1r-1][car_1c]!= '*'& grid[car_2r-1][car_2c]!='*')
        {
           grid[car_1r][car_1c]=' ';
           grid[car_1r-1][car_1c]=':';
           grid[car_2r][car_2c]=' ';
           grid[car_2r-1][car_2c]=':';
           car_1r--;
           car_2r--;
            //printf("\nUP UP UP\n");
        }
    }
    else if(dir==DOWN)

    {
        if(grid[car_1r+1][car_1c]!= '*'& grid[car_2r+1][car_2c]!='*')
      {
           grid[car_1r][car_1c]=' ';
           grid[car_1r+1][car_1c]=':';
           grid[car_2r][car_2c]=' ';
           grid[car_2r+1][car_2c]=':';
           car_1r++;
           car_2r++;
           //printf("\nDOWN\n");
      }
    }
    if(dir==LEFT)
    {
       if(grid[car_1r][car_1c-1]!= '*'& grid[car_2r][car_2c-1]!='*')
       {
           grid[car_1r][car_1c]=' ';
           grid[car_1r][car_1c-1]=':';
           grid[car_2r][car_2c]=' ';
           grid[car_2r][car_2c-1]=':';
           car_1c--;
           car_2c--;
      }
    }
    else if(dir==RIGHT)

    {
       if(grid[car_1r][car_1c+1]!= '*'& grid[car_2r][car_2c+1]!='*')
       {
           grid[car_2r][car_2c]=' ';
           grid[car_2r][car_2c+1]=':';
           grid[car_1r][car_1c]=' ';
           grid[car_1r][car_1c+1]=':';

           car_1c++;
           car_2c++;
       }
    }
}

void move_car2(enum move dir)
{
    if(dir==UP)
    {
        if(grid[car2_1r-1][car2_1c]!= '*'& grid[car2_2r-1][car2_2c]!='*')
        {
           grid[car2_1r][car2_1c]=' ';
           grid[car2_1r-1][car2_1c]=';';
           grid[car2_2r][car2_2c]=' ';
           grid[car2_2r-1][car2_2c]=';';
           car2_1r--;
           car2_2r--;
            //printf("\nUP UP UP\n");
        }
    }
    else if(dir==DOWN)

    {
        if(grid[car2_1r+1][car2_1c]!= '*'& grid[car2_2r+1][car2_2c]!='*')
      {
           grid[car2_1r][car2_1c]=' ';
           grid[car2_1r+1][car2_1c]=';';
           grid[car2_2r][car2_2c]=' ';
           grid[car2_2r+1][car2_2c]=';';
           car2_1r++;
           car2_2r++;
           //printf("\nDOWN\n");
      }
    }
    if(dir==LEFT)
    {
       if(grid[car2_1r][car2_1c-1]!= '*'& grid[car2_2r][car2_2c-1]!='*')
       {
           grid[car2_1r][car2_1c]=' ';
           grid[car2_1r][car2_1c-1]=';';
           grid[car2_2r][car2_2c]=' ';
           grid[car2_2r][car2_2c-1]=';';
           car2_1c--;
           car2_2c--;
      }
    }
    else if(dir==RIGHT)

    {
       if(grid[car2_1r][car2_1c+1]!= '*'& grid[car2_2r][car2_2c+1]!='*')
       {
           grid[car2_2r][car2_2c]=' ';
           grid[car2_2r][car2_2c+1]=';';
           grid[car2_1r][car2_1c]=' ';
           grid[car2_1r][car2_1c+1]=';';

           car2_1c++;
           car2_2c++;
       }
    }
}