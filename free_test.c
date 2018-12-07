#include <stdlib.h>
#include <stdio.h>


#include "malloc.h"

//Tests _free() and _malloc()

int main ( int argc, char* argv[] )
{
  printf("_free() test\n\n");
  char* A = NULL;
  A = (char*) _malloc (10);
  A[0] = 'A'; A[1] = 'B'; A[2] = '\0';

  printf("Address of A is %p\n", A );

  char* B = NULL;
  B = (char*) _malloc (10);
  B[0] = 'A'; B[1] = 'B'; B[2] = '\0';
  printf("\nAddress of B is %p\n", B );

  printf( "\nFreeing A to allow space for new allocation\n");
  _free (A);

  char* C = NULL;
  C = (char*) _malloc (10);
  C[0] = 'A'; C[1] = 'B'; C[2] = '\0';
  printf("\nAddress of C is %p\n", C );

  return 0;
}
