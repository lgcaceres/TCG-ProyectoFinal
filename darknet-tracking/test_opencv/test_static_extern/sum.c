#include "sum.h"

int myfoo(int x, int y){
	extern int I; //init once
	return x + y + I++;
}