#include <stdlib.h>
#include <stdio.h>


#include "malloc.h"

//Tests _realloc() and _malloc()

int main ( int argc, char* argv[] )
{
  printf("_realloc() test\n\n");

  char* A = NULL;
  A = (char*) _malloc (4);
  A[0] = 'A'; A[1] = 'B'; A[2] = 'C'; A[3] = 'D';

  printf("A is : ");
  for(int i = 0; i < 4; i++)
  {
    printf( "%c", A[i] );
  }
  printf("\nA address: %p\n", A);

  printf("\nMake size smaller (4 -> 2)\n");
  A = _realloc(A, 2);

  printf("A is : ");
  for(int i = 0; i < 2; i++)
  {
    printf( "%c", A[i] );
  }
  printf("\nA address: %p\n", A);

  printf("\nMake size bigger (2 -> 10)\n");
  A = (char*) _realloc(A, 10);

  A[0] = 'A'; A[1] = 'B'; A[2] = 'C'; A[3] = 'D'; A[4] = 'E';
  A[5] = 'C'; A[6] = 'D'; A[7] = 'E'; A[8] = 'F'; A[9] = 'G';

  printf("A is : ");
  for(int i = 0; i < 10; i++)
  {
    printf( "%c", A[i] );
  }
  printf("\nA address: %p\n", A);

  return 0;
}
