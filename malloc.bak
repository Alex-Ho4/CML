#include <stdlib.h>

//For testing
#include <stdio.h>
#include <string.h>

#include "malloc.h"

#define SIZE 1000000
#define META_SIZE sizeof(char) + sizeof(size_t)

// the big cheat
static char X[SIZE] = {'\0'};

void *_malloc(size_t size)
{
  //Initialize block of data if first malloc
  if(X[0] == '\0')
  {
    X[0] = 'i';
    X[1] = 'f';
    //Set size of initial block as entire block size
    *(size_t*)(&X[2]) = sizeof(X)-(sizeof(char) + META_SIZE);
  }

  //keep track of block size when going through
  size_t bsize = 0;
  for(int i = 1; i < SIZE;)
  {
    if(i > SIZE)
    {
      return NULL;
    }

    //Get size of current block
    bsize = *(size_t*)(&X[i+1]);

    if(X[i] == 'f' && *(size_t*)&X[i+1] >= size)
    {
      //Set block to allocated and set size
      X[i] = 'a';
      *(size_t*)(&X[i+1]) = size;

      //if next size is less than size of meta data, don't allocate next block
      size_t next_size = (bsize - (META_SIZE + size));
      if(next_size > META_SIZE)
      {
        //Create next block of memory (set free flag and size)
        X[i+META_SIZE+size] = 'f';
        *(size_t*)(&X[i+1+META_SIZE+size]) = next_size;
      }

      return (void*) &X[i+META_SIZE];
    }
    else
    {
      //Skip ahead by current block size
      i += bsize + META_SIZE;
    }
  }

  return NULL;
}

void _free(void *ptr)
{
  size_t prev = 0;
  //search for ptr
  for(int i = 1; i < SIZE; i += (*(size_t*)(&X[i+1]) + META_SIZE))
  {
    if((void*)(&X[i+META_SIZE]) == ptr)
    {
      //Free the block by changing header
      X[i] = 'f';

      //Check ahead for free slot to combine
      size_t next = i + META_SIZE + *(size_t*)(&X[i+1]);
      if(X[next] == 'f')
      {
        //combine two free slots
        *(size_t*)(&X[i+1]) = *(size_t*)(&X[i+1]) + META_SIZE + *(size_t*)(&X[next+1]);

        //removes ptr and data
        *(char*)(&X[i+META_SIZE]) = '\0';
        ptr = NULL;
        break;
      }

      //Check behind for free slot to combine
      if(X[prev] == 'f')
      {
        //combine two free slots
        *(size_t*)(&X[prev+1]) = *(size_t*)(&X[prev+1]) + META_SIZE + *(size_t*)(&X[i+1]);

        //removes ptr and data
        *(char*)(&X[i+META_SIZE]) = '\0';
        ptr = NULL;
        break;
      }

      //removes ptr and data
      *(char*)(&X[i+META_SIZE]) = '\0';
      ptr = NULL;
      break;
    }
    else
    {
      prev = i;
    }
  }
}

void *_calloc(size_t nmemb, size_t size)
{
  //get actual size
  size_t asize = nmemb * size;

  if(X[0] == '\0')
  {
    X[0] = 'i';
    X[1] = 'f';
    *(size_t*)(&X[2]) = sizeof(X)-(sizeof(char) + META_SIZE);
  }

  //keep track of block size
  size_t bsize = 0;
  for(int i = 1; i < SIZE;)
  {
    if(i > SIZE)
    {
      return NULL;
    }

    //Get size of current block
    bsize = *(size_t*)(&X[i+1]);

    if(X[i] == 'f' && *(size_t*)&X[i+1] >= asize)
    {
      //Set block to allocated and set size
      X[i] = 'a';
      *(size_t*)(&X[i+1]) = asize;

      //if next size is less than size of meta data, don't allocate next block
      size_t next_size = (bsize - (META_SIZE + asize));
      if(next_size > META_SIZE)
      {
        //Create next block of memory (set free flag and size)
        X[i+META_SIZE+asize] = 'f';
        *(size_t*)(&X[i+1+META_SIZE+asize]) = next_size;
      }

      //Zero the new block
      for(size_t k = i+META_SIZE; k < i+META_SIZE+asize; k++)
      {
        X[k] = '\0';
      }

      return (void*) &X[i+META_SIZE];
    }
    else
    {
      //Skip ahead by current block size
      i += bsize + META_SIZE;
    }
  }

  return NULL;
}

void *_realloc(void *ptr, size_t size)
{
  //Get and store block data in temp
  char temp[SIZE];
  size_t tsize = 0;
  int i = 1;
  for(; i < SIZE; i += (*(size_t*)(&X[i+1]) + META_SIZE))
  {
    if((void*)(&X[i+META_SIZE]) == ptr)
    {
      tsize = *(size_t*)&X[i+1];
      for(int k = 0; k < tsize; k++)
      {
        temp[k] = X[i+META_SIZE+k];
      }
      break;
    }
  }

  //Store data in new spot
  //keep track of block size
  size_t bsize = 0;
  for(int i = 1; i < SIZE;)
  {
    if(i > SIZE)
    {
      return NULL;
    }

    //Get size of current block
    bsize = *(size_t*)(&X[i+1]);

    if(X[i] == 'f' && *(size_t*)&X[i+1] >= size)
    {
      //Set block to allocated and set size
      X[i] = 'a';
      *(size_t*)(&X[i+1]) = size;

      //Store data in block
      size_t tsize = *(size_t*)&X[i+1];
      for(int k = 0; k < tsize; k++)
      {
        X[i+META_SIZE+k] = temp[k];
        //printf("%c, %c\n", X[i+META_SIZE+k], temp[k]);
      }

      //if next size is less than size of meta data, don't allocate next block
      size_t next_size = (bsize - (META_SIZE + size));
      if(next_size > META_SIZE)
      {
        //Create next block of memory (set free flag and size)
        X[i+META_SIZE+size] = 'f';
        *(size_t*)(&X[i+1+META_SIZE+size]) = next_size;
      }

      //free the pointer before returning
      _free(ptr);
      return (void*) &X[i+META_SIZE];
    }
    else
    {
      //Skip ahead by current block size
      i += bsize + META_SIZE;
    }
  }

  _free(ptr);
  return NULL;
}
