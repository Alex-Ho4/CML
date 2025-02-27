#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "malloc.h"

static inline unsigned long long rdtsc (void)
{
   unsigned int hi,lo;
   __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
   return ( (unsigned long long) lo) | ( (unsigned long long) hi<<32 ) ;
}
double diffTime ( struct timespec t0, struct timespec t1 )
{
   return t1.tv_sec - t0.tv_sec +  (t1.tv_nsec - t0.tv_nsec) / 1e9;
}

int main ( int argc, char* argv[] )
{
  //_malloc
  {
    char* A = NULL;
    long long unsigned int t0;
    long long unsigned int t1;
    long long unsigned int min = 0xfffffff; // a big number
    long long unsigned int max = 0.0;       // a small number
    // ignore the time on the first one
    A = (char*) _malloc (10);
    for (int i=0;i<100;i++)
    {
       t0 = rdtsc ();
       A = (char*) _malloc (10);
       t1 = rdtsc ();
       unsigned long long int dt = t1 - t0;
       // might want to print dt out and graph it
       printf (" %lld\n", dt );
       if (dt < min)
         min = dt;
       if (dt >max)
         max = dt;
    }
    printf ( "min = %lld max = %lld \n", min, max );
    _free(A);
  }

  //_free
  {
    char* A[100];
    long long unsigned int t0;
    long long unsigned int t1;
    long long unsigned int min = 0xfffffff; // a big number
    long long unsigned int max = 0.0;       // a small number
    // ignore the time on the first one
    for (int i=0;i<100;i++)
    {
      A[i] = (char*) _malloc (10);
    }
    for (int i=0;i<100;i++)
    {
      t0 = rdtsc ();
      _free(A[i]);
      t1 = rdtsc ();
      unsigned long long int dt = t1 - t0;
      // might want to print dt out and graph it
      printf (" %lld\n", dt );
      if (dt < min)
        min = dt;
      if (dt >max)
        max = dt;
    }
    printf ( "min = %lld max = %lld \n", min, max );
    _free((char*)A[0]);
  }

  //_calloc
  {
    char* A = NULL;
    long long unsigned int t0;
    long long unsigned int t1;
    long long unsigned int min = 0xfffffff; // a big number
    long long unsigned int max = 0.0;       // a small number
    // ignore the time on the first one
    A = (char*) _calloc (1,10);
    for (int i=0;i<100;i++)
    {
       t0 = rdtsc ();
       A = (char*) _calloc (1,10);
       t1 = rdtsc ();
       unsigned long long int dt = t1 - t0;
       // might want to print dt out and graph it
       printf (" %lld\n", dt );
       if (dt < min)
         min = dt;
       if (dt >max)
         max = dt;
    }
    printf ( "min = %lld max = %lld \n", min, max );
    _free(A);
  }

  //_realloc
  {
    char* A[100];
    long long unsigned int t0;
    long long unsigned int t1;
    long long unsigned int min = 0xfffffff; // a big number
    long long unsigned int max = 0.0;       // a small number
    // ignore the time on the first one
    for (int i=0;i<100;i++)
    {
      A[i] = (char*) _malloc (10);
    }
    for (int i=0;i<100;i++)
    {
       t0 = rdtsc ();
       A[i] = (char*) _realloc ((char*)A[i], 20);
       t1 = rdtsc ();
       unsigned long long int dt = t1 - t0;
       // might want to print dt out and graph it
       printf (" %lld\n", dt );
       if (dt < min)
         min = dt;
       if (dt >max)
         max = dt;
    }
    printf ( "min = %lld max = %lld \n", min, max );
    _free((char*)A[0]);
  }
  return 0;
}
