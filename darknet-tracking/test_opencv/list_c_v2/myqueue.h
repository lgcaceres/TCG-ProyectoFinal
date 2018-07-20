
#ifndef QUEUE_H
#define QUEUE_H


#include <stdio.h>
#include <stdlib.h>

#include "mytracking_obj.h"

#include "mycommon.h"



//#define SIZEOF_BUFF 4096
//#define LIMIT_QUEUE 10


//struct tracking_obj;	
typedef struct tracking_obj tracking_obj;

typedef struct mynode mynode;
typedef struct queue queue;


typedef struct Point Point;
typedef struct Rectangle Rectangle;


struct mynode{
  Rectangle* data_rect;
  mynode* next;
};



struct queue{
  mynode* front;
  mynode* rear;
  int limit;
};



void free_queue(queue** myqueue);
void free_mynode_queue(mynode** pnode);
void create_queue(queue** myqueue);
void create_mynode_queue(mynode** pnode);
void enqueue_rectangle(queue* myqueue, Rectangle* rect);
void dequeue_rectangle(queue* myqueue);
//void print_queue_rectagles(queue* myqueue, char buffer[SIZEOF_BUFF],FILE* fp);
void print_queue_rectagles(queue* myqueue, FILE* fp);

double eval_distanceTotal_queue(queue* myqueue);

#endif //end QUEUE_H
