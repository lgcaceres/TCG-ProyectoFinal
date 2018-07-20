#include <stdio.h>



main() {
   FILE *fp;
   fp = fopen("test22.txt", "a");
   char buff[500]={0};
   char test[]="esta es una prueba";
   fprintf(fp, "This is testing for fprintf...\n");

   fputs("This is testing for fputs...\n", fp);
   fprintf(fp, test);
   fclose(fp);
}