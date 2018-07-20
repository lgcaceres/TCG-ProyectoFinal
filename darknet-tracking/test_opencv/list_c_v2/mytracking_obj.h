

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
   int flag; //0-1
   int perdida; //maximo 10

   double velocidad;
   double distancia;
   
   int pointcenterX;
   int pointcenterY;

   Rectangle* bounding_box;
   //agregar cola para la persistencia del recorrido.
   //Rectangle recorrido_bounding_box[10];
   queue* queue_rectangles;
};


void free_new_tracking_obj(tracking_obj** obj);
void create_new_tracking_obj(tracking_obj** obj);
void update_tracking_obj(tracking_obj* obj, Rectangle* rect1);


void update_pointCenter(tracking_obj* obj, Rectangle* rect1);

double distancia_eu_2rect(Rectangle* rect1, Rectangle* rect2);



#endif //end TRACKING_OBJ_H
