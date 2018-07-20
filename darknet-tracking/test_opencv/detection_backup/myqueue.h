
#ifndef QUEUE_H
#define QUEUE_H


#include <stdio.h>
#include <stdlib.h>

#include "mytracking_obj.h"

#include "mycommon.h"



typedef struct tracking_obj tracking_obj;

typedef struct mynode mynode;
typedef struct queue queue;


typedef struct point point;
typedef struct rectangle rectangle;


struct mynode{
  rectangle* data_rect;
  mynode* next;
};



void myNodeQueue_create(mynode** pnode);
void myNodeQueue_free(mynode** pnode);

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


struct queue{
  mynode* front;
  mynode* rear;
  int limit;
};

void myQueue_create(queue** myqueue);
void myQuee_free(queue** myqueue);

void myQueue_enqueue(queue* myqueue, rectangle* rect);
void myQueue_dequeue(queue* myqueue);

void print_queue_rectagles(queue* myqueue, FILE* fp);

double eval_distanceTotal_queue(queue* myqueue);

#endif //end QUEUE_H

