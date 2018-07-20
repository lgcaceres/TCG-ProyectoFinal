#include <stdio.h>
#include <math.h>

typedef struct 
{
	int x;
	int y;
}Point;

typedef struct 
{
	Point topleft;
	Point bottomright; 
	
}Rectangle;


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



void overlap(Rectangle A, Rectangle B)
{
	int w1=fabs(A.bottomright->x-A.topleft->x);
	int h1=fabs(A.bottomright->y-A.topleft->y);
	int w2=fabs(B.bottomright->x-B.topleft->x);
	int h2=fabs(B.bottomright->y-B.topleft->y);


	float SA=w1*h1;
	float SB=w2*h2;

	float iLeft=max(A.topleft->x,B.topleft->x);
	float iRight=min(A.bottomright->x,B.bottomright->x);
	float iTop=max(A.topleft->y,B.topleft->y);
	float iBottom=min(A.bottomright->y,B.bottomright->y);

    float si = max(0, iRight - iLeft) * max(0, iBottom - iTop);
    
    float su=SA + SB -si;
    float overlap=si/su;
    printf("overlap es: %f \n",overlap);

}



int main()
{
	Point p1;
	Point p2;
	p1->x=20;
	p1->y=20;
	p2->x=30;
	p2->y=30;
	Point p3;
	Point p4;
	p3->x=12;
	p3->y=12;
	p4->x=100;
	p4->y=110;
	Rectangle rec1;
	Rectangle rec2;
	rec1.topleft=p1;
	rec1.bottomright=p2;
	rec2.topleft=p3;
	rec2.bottomright=p4;
	overlap(rec1,rec2);
	return 0;
}