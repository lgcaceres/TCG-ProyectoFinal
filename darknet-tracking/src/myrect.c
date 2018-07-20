
#include "myrect.h"


void myPoint_create(point** pp){
	point* temp = (point*)malloc(sizeof(point));
	myPoint_init_create(temp);
	(*pp) = temp;
	return;
}

void myPoint_init_create(point* p){
	p->x = -1;
	p->y = -1;
	return;
}


void myPoint_free(point* pp){
	free(pp);
	pp=NULL;
	return;
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

void myRectangle_create(rectangle** rect){
	rectangle* temp = (rectangle*)malloc(sizeof(rectangle));
	myRectangle_init_create(temp);
	(*rect)=temp;
	return;
}

void myRectangle_init_create(rectangle* rect){
	myPoint_create( &(rect->topleft) );
	myPoint_init_create(rect->topleft);

	myPoint_create( &(rect->bottomright) );
	myPoint_init_create(rect->bottomright);
	return;
}

void myRectangle_free(rectangle* rect){
	myPoint_free( rect->topleft);
	myPoint_free( rect->bottomright);
	rect = NULL;
	return;
}
/*
void myRectangle_fill(rectangle* myrect, int p1x, int p1y, int p2x, int p2y){
	myrect->topleft->x = p1x;
	myrect->topleft->y = p1y;

	myrect->bottomright->x = p2x;
	myrect->bottomright->y = p2y;
	return;
}
*/


void myRectangle_fill(rectangle* myrect, int left, int top, int right, int bot){
	myrect->topleft->x = left;
	myrect->topleft->y = top;

	myrect->bottomright->x = right;
	myrect->bottomright->y = bot;
	return;
}


int myRectangle_isPoint(rectangle* myrect){
	// -1  es un punto
	//  0  es cuadrado
	//  1  es linea
	if(myrect->topleft->x != myrect->bottomright->x)
	{
		if(myrect->topleft->y != myrect->bottomright->y)
		{
			return 0; 
		}
		return 1;
	}
	if(myrect->topleft->y != myrect->bottomright->y)
	{
		if(myrect->topleft->x != myrect->bottomright->x)
		{
			return 0;
		}
		return 1;
	}
	return -1;
}


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


int max(int a, int b)
{
	if(a<b)
		return b;
	else return a;
}


int min(int a, int b)
{
	if(a<b)
		return a;
	else return b;
}


//OJO
//agregar caso donde:
//		-un area menor esta contenida dentro de otra mayor
//		-el resultado de esto deberia ser 100% 
double myRectangle_overlap(rectangle* rectA, rectangle* rectB)
{
	double overlapp = 0;
	int w1 = fabs(rectA->bottomright->x - rectA->topleft->x);
	int h1 = fabs(rectA->bottomright->y - rectA->topleft->y);
	int w2 = fabs(rectB->bottomright->x - rectB->topleft->x);
	int h2 = fabs(rectB->bottomright->y - rectB->topleft->y);
	
	double SA = w1*h1;
	double SB = w2*h2;

	double iLeft    = max(rectA->topleft->x     ,rectB->topleft->x);
	double iRight   = min(rectA->bottomright->x ,rectB->bottomright->x);
	double iTop  	= max(rectA->topleft->y     ,rectB->topleft->y);
	double iBottom  = min(rectA->bottomright->y ,rectB->bottomright->y);

	double si = max(0, iRight - iLeft) * max(0, iBottom - iTop);
	double su = SA + SB - si;

	overlapp = si / su;
	return overlapp; 
}



void myRectangle_copy(rectangle* rect1, rectangle* rect2){
	if( rect1 == NULL ){
		printf("Error, puntero vacio, rect1.\n");
		return;
	}
	if( rect2 == NULL ){
		printf("Error, puntero vacio, rect2.\n");
		return;
	}
	rect1->topleft->x 	  = rect2->topleft->x;
	rect1->topleft->y 	  = rect2->topleft->y;
	rect1->bottomright->x = rect2->bottomright->x;
	rect1->bottomright->y = rect2->bottomright->y;
	return;
}



double myRectangle_distancia_eu_2rect(rectangle* rect1, rectangle* rect2){
  if( rect1 == NULL ){
    printf("Error, puntero vacio, rect1.\n");
    //myRectangle_create(&rect2);
    return -1.0;
  }

  if( rect2 == NULL ){
    printf("Error, puntero vacio, rect2.\n");
    //myRectangle_create(&rect2);
    return -1.0;
  }

  //printf("(%d,%d,%d,%d)\n",rect1->topleft->x,rect1->topleft->y,rect2->topleft->x,rect2->topleft->y);

  double x1 = rect1->topleft->x + fabs(rect1->bottomright->x - rect1->topleft->x)/2;
  double y1 = rect1->topleft->y + fabs(rect1->bottomright->y - rect1->topleft->y)/2;

  double x2 = rect2->topleft->x + fabs(rect2->bottomright->x - rect2->topleft->x)/2;
  double y2 = rect2->topleft->y + fabs(rect2->bottomright->y - rect2->topleft->y)/2;

  double dist = sqrt( pow(x1-x2,2) + pow(y1-y2,2) );

  return dist;
}