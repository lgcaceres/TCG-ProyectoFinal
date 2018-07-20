

#ifndef MYLIST_H
#define MYLIST_H


#include <stdio.h>
#include <stdlib.h>

#include "mytracking_obj.h"
#include "myqueue.h"
#include "myrect.h"
#include <string.h>

#include "mycommon.h"
//#define SIZEOF_BUFF 4096
//#define LIMIT_PERDIDA 3



typedef struct mynodelist mynodelist;
typedef struct tracking_obj tracking_obj;

typedef struct point point;
typedef struct rectangle rectangle;


typedef struct mylist mylist;




struct mynodelist{
       tracking_obj* data_obj;
       mynodelist* next;
       mynodelist* prev;
  //struct mynodelist* prev;
};

void myNodeList_create(mynodelist** n);
void myNodeList_free(mynodelist** n);



///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

struct mylist{
  mynodelist* root;
};


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


//void create_structure(mylist** l);

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


void myList_create(mylist** l);
void myList_free(mylist** l);

void myList_insert_1_rect2(mylist* l, rectangle* myrect, double threshold_rectangle, int number_frame);
void myList_insert_2_rect2(mynodelist* pnode, rectangle* myrect, double threshold_rectangle, int number_frame);


void myList_update_perdida(mylist* l, int number_frame);
void myList_update_per2(mynodelist* pnode, int number_frame);
void myList_update_perdida_v2(mylist* l, int number_frame);


void myList_limpiar_perdida_recursiva_interior(mynodelist** pnode);
void myList_limpiar_perdida_recursiva(mylist* l);

void myList_limpiar_perdida(mylist* l);


void myList_print(mylist* l, FILE* fp);
void myList_print2(mylist* l, FILE* fp);


double myList_buscar_rectangle_returnVeloc(mylist* l, int left, int right, int top, int bot);
double myList_buscar_rectangle_returnDistance(mylist* l, int left, int right, int top, int bot);



void myList_update_distancia(mylist* l);

void myList_update_velocidad(mylist* l);


#endif //end MYLIST_H
