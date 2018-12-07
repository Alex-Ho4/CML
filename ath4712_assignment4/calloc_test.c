#include <stdlib.h>
#include <stdio.h>


#include "malloc.h"



int main ( int argc, char* argv[] )
{
  printf("_calloc() test\n\n");

  char* A = NULL;
  A = (char*) _malloc (4);
  A[0] = 'A'; A[1] = 'B'; A[2] = 'C'; A[3] = 'D';

  printf("A is : ");
  for(int i = 0; i < 4; i++)
  {
    printf( "%c", A[i] );
  }
  printf("\nA address: %p\n", A);

  printf("\nFreeing block\n");
  _free(A);

  printf("A is : ");
  for(int i = 0; i < 4; i++)
  {
    printf( "%c", A[i] );
  }
  printf("\nA address: %p\n", A);

  printf("\nCreate block with calloc\n");

  A = (char*) _calloc(1, 4);

  printf("A is : ");
  for(int i = 0; i < 4; i++)
  {
    printf( "%c", A[i] );
  }
  printf("\nA address: %p\n", A);

  return 0;
}
