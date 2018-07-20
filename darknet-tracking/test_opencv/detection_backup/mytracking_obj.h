

#ifndef TRACKING_OBJ_H
#define TRACKING_OBJ_H


#include "mytracking_obj.h"
#include "mylist.h"
#include "myrect.h"
#include "myqueue.h"


#include <math.h>
#include <stdio.h>

#include "mycommon.h"
//#define VACIOSTRING "vacio-string"



//extern struct mynode;
typedef struct queue queue;
//extern typedef struct mynode mynode;
//extern typedef struct queue queue;

typedef struct tracking_obj tracking_obj;



struct tracking_obj{
   char *name;
   int   flag; //0-1
   int   perdida; //maximo 10

   double velocidad;
   double distancia;
   
   int pointcenterX;
   int pointcenterY;

   rectangle* bounding_box;
   //agregar cola para la persistencia del recorrido.
   //Rectangle recorrido_bounding_box[10];
   queue* queue_rectangles;
};


void myTrackingObj_create(tracking_obj** obj);
void myTrackingObj_free(tracking_obj** obj);

void myTrackingObj_update(tracking_obj* obj, rectangle* rect1);

void mytrackingObj_updatePointCenter(tracking_obj* obj, rectangle* rect1);

double myTrackingObj_distancia_eu_2rect(rectangle* rect1, rectangle* rect2);


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////



#endif //end TRACKING_OBJ_H
