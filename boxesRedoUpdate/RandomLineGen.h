#ifndef RANDOMLINEGEN_H_INCLUDED
#define RANDOMLINEGEN_H_INCLUDED

#include <stdlib.h>

int
randomnum (int high)
{
  //srand(time(0));
  int x = rand () % (high*2 + 1);
  return x;
}

int
randomeven (int high)
{
  int x;
  //srand(time(0));
  if (high % 2 == 0)
    {
      x = 2 * (rand () % ((high + 1) / 2));
    }
  else
    {
      x = 2 * (rand () % ((high + 1) / 2));
    }
  return x;
}

int
randomodd (int high)
{
  int x;
  //srand(time(0));
  x = 2* (rand() % (high / 2)) + 1;
  return x;
}

tuple randomline (int gridDim ,char arr[gridDim*2-1][gridDim*2-1])
{
  tuple lcoor;
  int x = randomnum (gridDim*2-1);
  lcoor.x = x;
  int y;
  
  

  if (x % 2 == 0)
  {
    y = randomodd (gridDim*2-1);
  }
  else
    {
      y = randomeven (gridDim*2-1);
    }
  lcoor.y = y;

  if (arr[x][y] == -1 && x < 2*gridDim-1 && y < 2*gridDim-1)
    {
      if (x % 2 == 0 && y % 2 == 1)
	  {
	    arr[x][y] = '-';
	  }
      if (x % 2 == 1 && y % 2 == 0)
	  {
	    arr[x][y] = '|';
	  }
    return lcoor;
    }
  else
    {
      randomline (gridDim , arr);
    }
  
}

#endif // RANDOMLINEGEN_H_INCLUDED