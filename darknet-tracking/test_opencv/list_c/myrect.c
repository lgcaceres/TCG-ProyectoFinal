
#include "myrect.h"


void create_myPoint(Point** pp){
	Point* temp = (Point*)malloc(sizeof(Point));
		   temp->x = -1;
		   temp->y = -1;
	return;
}

void init_myPoint(Point* p){
	p->x = -1;
	p->y = -1;
}


void free_myPoint(Point* pp){
	//printf("llamanado a: free(pp);11\n");
	free(pp);
	//printf("llamanado a: free(pp);22\n");
	return;
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

void create_myRectangle(Rectangle** rect){
	Rectangle* temp = (Rectangle*)malloc(sizeof(Rectangle));
	init_myPoint(&(temp->topleft));
	init_myPoint(&(temp->bottomright));
	(*rect)=temp;
}

void free_myRectangle(Rectangle** rect){
	printf("llamando a: free_myPoint1-11\n");
	free_myPoint( &((*rect)->topleft) );
	//free( &((*rect)->topleft) );
	printf("llamando a: free_myPoint1-22\n");


	printf("llamando a: free_myPoint2-11\n");
	free_myPoint( &((*rect)->bottomright) );
	//free( &((*rect)->bottomright) );
	printf("llamando a: free_myPoint2-22\n");
	return;
}

void fill_myRectangle(Rectangle* myrect, int p1x, int p1y, int p2x, int p2y){
	myrect->topleft.x = p1x;
	myrect->topleft.y = p1y;
	myrect->bottomright.x = p2x;
	myrect->bottomright.y = p2y;
}



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



float my_overlap(Rectangle A, Rectangle B)
{
	int w1=fabs(A.bottomright.x-A.topleft.x);
	int h1=fabs(A.bottomright.y-A.topleft.y);
	int w2=fabs(B.bottomright.x-B.topleft.x);
	int h2=fabs(B.bottomright.y-B.topleft.y);


	float SA=w1*h1;
	float SB=w2*h2;

	float iLeft=max(A.topleft.x,B.topleft.x);
	float iRight=min(A.bottomright.x,B.bottomright.x);
	float iTop=max(A.topleft.y,B.topleft.y);
	float iBottom=min(A.bottomright.y,B.bottomright.y);

    float si = max(0, iRight - iLeft) * max(0, iBottom - iTop);
    
    float su=SA + SB -si;
    float overlap=si/su;
    //printf("overlap es: %f \n",overlap);
    return overlap;

}


//OJO
//agregar caso donde:
//		-un area menor esta contenida dentro de otra mayor
//		-el resultado de esto deberia ser 100% 
double myoverlap_rectangle(Rectangle* A, Rectangle* B)
{
  double overlapp = 0;
  int w1 = fabs(A->bottomright.x - A->topleft.x);
  int h1 = fabs(A->bottomright.y - A->topleft.y);
  int w2 = fabs(B->bottomright.x - B->topleft.x);
  int h2 = fabs(B->bottomright.y - B->topleft.y);

  double SA = w1*h1;
  double SB = w2*h2;

  double iLeft    = max(A->topleft.x     ,B->topleft.x);
  double iRight   = min(A->bottomright.x ,B->bottomright.x);
  double iTop  	  = max(A->topleft.y     ,B->topleft.y);
  double iBottom  = min(A->bottomright.y ,B->bottomright.y);

    double si = max(0, iRight - iLeft) * max(0, iBottom - iTop);
    
    double su = SA + SB - si;

    overlapp = si / su;
    //printf("overlap es11: %lf \n",overlapp);
    //double zzzz = 465;
    //printf("overlap es22 zzzz: %lf \n",zzzz);
    return overlapp; 
}

void copy_rectangle(Rectangle* rect1, Rectangle* rect2){
	if( rect1 == NULL ){
		printf("Error, puntero vacio, rect1.\n");
		return;
	}
	if( rect2 == NULL ){
		printf("Error, puntero vacio, rect2.\n");
		//create_myRectangle(&rect2);
		return;
	}
	rect1->topleft.x 	 = rect2->topleft.x;
	rect1->topleft.y 	 = rect2->topleft.y;
	rect1->bottomright.x = rect2->bottomright.x;
	rect1->bottomright.y = rect2->bottomright.y;
	return;
}
