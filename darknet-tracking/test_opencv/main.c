#include <string.h>




int main(){

	float thresh_temp = 0.0;
	char  labelstr_high[30] = {0};

	char  labelstr_high1[30] = "holaestaesunaprueba";
	char  labelstr_high2[30] = "luigy";

    sprintf(labelstr_high, "%s", labelstr_high1 );
    printf("%s:\n", labelstr_high );
         
    sprintf(labelstr_high, "%s", labelstr_high2 );
	printf("%s:\n", labelstr_high );


	char strtemp[]="luigy";
	if(0==strcmp(labelstr_high,strtemp))
       printf("%s<:  ok\n ", labelstr_high);

    return 0;
}