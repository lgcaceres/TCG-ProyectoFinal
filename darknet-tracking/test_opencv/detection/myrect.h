

#ifndef RECT_H
#define RECT_H



#include "mycommon.h"
#include "mycommon.h"



typedef struct point point;
typedef struct rectangle rectangle;

///////////////////////////////////////////////////
///////////////////////////////////////////////////

struct point{
	int x;
	int y;
};

void myPoint_create(point** pp);
void myPoint_init_create(point* p);
void myPoint_free(point* pp);

///////////////////////////////////////////////////
///////////////////////////////////////////////////

struct rectangle{
	point* topleft;
	point* bottomright;
};

void myRectangle_create(rectangle** rect);
void myRectangle_free(rectangle* rect);

void myRectangle_init_create(rectangle* rect);
void myRectangle_fill(rectangle* myrect, int p1x, int p1y, int p2x, int p2y);

///////////////////////////////////////////////////
///////////////////////////////////////////////////

int max(int a, int b);
int min(int a, int b);

double myRectangle_overlap(rectangle* rectA, rectangle* rectB);

void myRectangle_copy(rectangle* rect1, rectangle* rect2);

double myRectangle_distancia_eu_2rect(rectangle* rect1, rectangle* rect2);


#endif //end RECT_H
