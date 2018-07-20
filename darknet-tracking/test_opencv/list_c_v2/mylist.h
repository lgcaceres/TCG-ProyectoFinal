

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

typedef struct Point Point;
typedef struct Rectangle Rectangle;


typedef struct mylist mylist;




struct mynodelist{
       tracking_obj* data_obj;
       mynodelist* next;
       mynodelist* prev;
  //struct mynodelist* prev;
};

struct mylist{
  mynodelist* root;
};


void create_mynodelist(mynodelist** n);
void free_mynodelist(mynodelist** n);

void create_mylist(mylist** l);

void my_insert_list2_rect(mynodelist* pnode, Rectangle* myrect, double threshold_rectangle);
void my_insert_list_rect(mylist* l, Rectangle* myrect, double threshold_rectangle);


void my_insert_list_rect2(mylist* l, Rectangle* myrect, double threshold_rectangle, int number_frame);
void my_insert_list2_rect2(mynodelist* pnode, Rectangle* myrect, double threshold_rectangle, int number_frame);

void update_perdida(mylist* l, int number_frame);
void update_per2(mynodelist* pnode, int number_frame);
void update_perdida_v2(mylist* l, int number_frame);



void limpiar_perdida_recursiva_interior(mynodelist** pnode);
void limpiar_perdida_recursiva(mylist* l);

void limpiar_perdida(mylist* l);





void print_list(mylist* l, FILE* fp);
void print_list2(mylist* l, FILE* fp);




double buscar_rectangle_returnVeloc(mylist* l, int left, int right, int top, int bot);
double buscar_rectangle_returnDistance(mylist* l, int left, int right, int top, int bot);



#endif //end MYLIST_H
