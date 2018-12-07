#include <stdlib.h>
#include "malloc.h"

#define SIZE 1000000
#define META_SIZE sizeof(char) + sizeof(size_t)

// the big cheat
static char X[SIZE] = {'\0'};
static int first_free = 1;

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
  for(int i = first_free; i < SIZE;)
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
      if((long)next_size > 0 && next_size > META_SIZE)
      {
        //Create next block of memory (set free flag and size)
        X[i+META_SIZE+size] = 'f';
        *(size_t*)(&X[i+1+META_SIZE+size]) = next_size;

        //if block allocated was the earliest free block, increment it to next free
        if(i == first_free)
        {
          first_free = i+META_SIZE+size;
        }
      }
      else if(i == first_free)
      {
        //If block was allocated was the earliest free data block AND
        //If a new block can't be made, find and set first_free
        for(int k = i; X[k] != 'f' && k < SIZE;)
        {
          k += META_SIZE + *(size_t*)(&X[k+1]);
          first_free = k;
        }
      }
      return (void*) &X[i+META_SIZE];
    }
    else
    {
      //Skip ahead by current block size
      i += bsize + META_SIZE;
      //In case it runs into a fragment
      while(X[i] != 'a' && X[i] != 'f')
      {
        i++;
      }
    }
  }

  return NULL;
}

void _free(void *ptr)
{
  size_t prev = 1;
  //search for ptr
  for(int i = 1; i < SIZE; i += (*(size_t*)(&X[i+1]) + META_SIZE))
  {

    if((void*)(&X[i+META_SIZE]) == ptr)
    {
      //Free the block by changing header
      X[i] = 'f';

      //Check ahead for free slot to combine
      size_t next = i + META_SIZE + *(size_t*)(&X[i+1]);
      if(next < SIZE && X[next] == 'f')
      {
        //combine two free slots
        *(size_t*)(&X[i+1]) = *(size_t*)(&X[i+1]) + META_SIZE + *(size_t*)(&X[next+1]);

        //clear meta data
        X[next] = '\0';
        *(size_t*)(&X[next+1]) = 0;

        //sets first_free to earliest possible free block
        if(i < first_free)
        {
          first_free = i;
        }

        break;
      }

      //Check behind for free slot to combine
      if(prev > META_SIZE+1 && X[prev] == 'f')
      {
        //combine two free slots
        *(size_t*)(&X[prev+1]) = *(size_t*)(&X[prev+1]) + META_SIZE + *(size_t*)(&X[i+1]);

        //clear meta data
        X[i] = '\0';
        *(size_t*)(&X[i+1]) = 0;

        //sets first_free to earliest possible free block
        if(prev < first_free)
        {
          first_free = prev;
        }

        break;
      }

      //sets first_free to earliest possible free block
      if(i < first_free)
      {
        first_free = i;
      }

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

  //Return null if total size is too large;
  if(asize > SIZE)
  {
    return NULL;
  }

  if(X[0] == '\0')
  {
    X[0] = 'i';
    X[1] = 'f';
    *(size_t*)(&X[2]) = sizeof(X)-(sizeof(char) + META_SIZE);
  }

  //keep track of block size
  size_t bsize = 0;
  for(int i = first_free; i < SIZE;)
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
      if((long)next_size > 0 && next_size > META_SIZE)
      {
        //Create next block of memory (set free flag and size)
        X[i+META_SIZE+asize] = 'f';
        *(size_t*)(&X[i+1+META_SIZE+asize]) = next_size;

        //if block allocated was the earliest free block, increment it to next free
        if(i == first_free)
        {
          first_free = i+META_SIZE+size;
        }
      }
      else if(i == first_free)
      {
        //If block was allocated was the earliest free data block AND
        //If a new block can't be made, find and set first_free
        for(int k = i; X[k] != 'f' && k < SIZE;)
        {
          k += META_SIZE + *(size_t*)(&X[k+1]);
          first_free = k;
        }
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
      //In case it runs into a fragment
      while(X[i] != 'a' && X[i] != 'f')
      {
        i++;
      }
    }
  }

  return NULL;
}

void *_realloc(void *ptr, size_t size)
{
  //Get and store block data in temp and its size into tsize
  char temp[SIZE];
  size_t tsize = 0;
  for(int i = 1; i < SIZE; i += (*(size_t*)(&X[i+1]) + META_SIZE))
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

  _free(ptr);

  //Store data in new spot
  //keep track of block size
  size_t bsize = 0;
  for(int i = first_free; i < SIZE;)
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

      //if size between next block is less than size of meta data, don't allocate next block
      size_t next_size = (bsize - (META_SIZE + size));
      if((long)next_size > 0 && next_size > META_SIZE)
      {
        //Create next block of memory (set free flag and size)
        X[i+META_SIZE+size] = 'f';
        *(size_t*)(&X[i+1+META_SIZE+size]) = next_size;

        //if block allocated was the earliest free block, increment it to next free
        if(i == first_free)
        {
          first_free = i+META_SIZE+size;
        }
      }
      else if(i == first_free)
      {
        //If block was allocated was the earliest free data block AND
        //If a new block can't be made, find and set first_free
        for(int k = i; X[k] != 'f' && k < SIZE;)
        {
          k += META_SIZE + *(size_t*)(&X[k+1]);
          first_free = k;
        }
      }
      //Store data in block, stopping if new size is less than requested
      for(int k = 0; k < tsize && k < size; k++)
      {
        X[i+META_SIZE+k] = temp[k];
      }
      return (void*) &X[i+META_SIZE];
    }
    else
    {
      //Skip ahead by current block size
      i += bsize + META_SIZE;
      //In case it runs into a fragment
      while(X[i] != 'a' && X[i] != 'f')
      {
        i++;
      }
    }
  }
  return NULL;
}
