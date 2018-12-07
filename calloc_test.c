#include <stdlib.h>
#include <stdio.h>


#include "malloc.h"



int main ( int argc, char* argv[] )
{
  char* A = NULL;
  A = (char*) _malloc (6);
  A[0] = 'A';
  A[2] = 'B';
  A[3] = 'C';
  A[4] = 'D';
  A[5] = 'E';
  printf("A ptr is %p\n", &A);
  for(int i = 0; i < 6; i++)
  {
    printf("A data is %d\n", A[i]);
  }

  _free(A);

  A = (char*) _calloc(6,1);
  printf("A ptr is %p\n", &A);
  for(int i = 0; i < 6; i++)
  {
    printf("A data is %d\n", A[i]);
  }
  return 0;
}
