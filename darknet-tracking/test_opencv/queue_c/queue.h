
#ifndef QUEUE_H
#define QUEUE_H


#include<stdio.h>
#include<stdlib.h>



struct mynode{
  int data;
  struct mynode* next;
};

typedef struct mynode mynode;


typedef struct{
  mynode* front;
  mynode* rear;
}queue;




#endif //end QUEUE_H
