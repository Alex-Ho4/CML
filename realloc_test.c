#include <stdlib.h>
#include <stdio.h>


#include "malloc.h"



int main ( int argc, char* argv[] )
{
   char* A = NULL;
   char* B = NULL;
   A = (char*) _malloc (3);
   A[0] = 'A'; A[1] = 'B'; A[2] = '\0';
   printf( "A is %s \n",A);

   B = _realloc (A, 5);
   _free(A);

   printf( "A is %s \n",A);

   B[2] = 'C'; B[3] = 'D'; B[4] = '\0';
   printf( "B is %s \n",B);

   A = NULL;
   A = (char*) _malloc (5);
   A[0] = 'A'; A[1] = 'B'; A[2] = '\0';
   printf( "A is %s \n",A);
   printf( "A PTR is %p \n",&A);

   A = _realloc (A, 3);

   printf( "A is %s \n",A);
   printf( "A PTR is %p \n",&A);
   return 0;
}
