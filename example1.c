#include <stdlib.h>
#include <stdio.h>


#include "malloc.h"



int main ( int argc, char* argv[] )
{
   char* A = NULL;
   A = (char*) _malloc (10);
   A[0] = 'A'; A[1] = 'B'; A[2] = '\0';
   printf( "A is %s \n",A);
   _free (A);
   // is A still equal to "AB"?
   printf( "A is %s \n",A);
   return 0;
}
