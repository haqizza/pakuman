#include "..\lib\functions.h"

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