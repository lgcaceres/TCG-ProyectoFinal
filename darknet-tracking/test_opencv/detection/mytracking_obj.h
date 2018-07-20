

#ifndef TRACKING_OBJ_H
#define TRACKING_OBJ_H


#include "mytracking_obj.h"
#include "myrect.h"

#include <math.h>
#include <stdio.h>

#include "mycommon.h"
#include <gmodule.h>



//extern struct mynode;
typedef struct rectangle rectangle;
//extern typedef struct mynode mynode;
//extern typedef struct queue queue;

typedef struct tracking_obj tracking_obj;



struct tracking_obj{
   char *name;
   int   flagUsed; //0-1
   int   lostBound; //maximo 10

   double velocidad;
   double distancia;
   
   int pointcenterX;
   int pointcenterY;

   rectangle* rootRect;
   GQueue* queue_rectangles;
};



void myTrackingObj_create(tracking_obj** obj);
void myTrackingObj_init_create(tracking_obj* obj);

void myTrackingObj_updateRootRect(tracking_obj* obj, rectangle* rect1);

void myTrackingObj_addQueue(tracking_obj* obj, rectangle* rect1);

void myTrackingObj_updateAllFlags(GList* mylist);

void myTrackingObj_deleletALLBoundingBoxLost(GList** mylist1);

void myTrackingObj_printListObjInFile(GList* mylist, FILE* fp);
void myTrackingObj_printTrackingObjInFile(tracking_obj* obj, FILE* fp);

void myTrackingObj_print2(tracking_obj* obj);
void myTrackingObj_print(GList* mylist);

void myTrackingObj_updateFlagUsed(tracking_obj* obj);

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

void myTrackingObj_free(tracking_obj* obj);

void mytrackingObj_updatePointCenter(tracking_obj* obj, rectangle* rect1);

void myTrackingObj_updateDistance(tracking_obj* obj);

void myTrackingObj_updateSpeed(tracking_obj* obj);


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

int myfoo_GCompareFunc(void* a, void* b);

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

#endif //end TRACKING_OBJ_H
