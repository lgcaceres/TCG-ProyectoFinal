
#include<stdio.h>
#include <math.h>
#include <string.h>



#include <time.h>
#include <stdlib.h>


#include "mycommon.h"


//#define SIZEOF_BUFF 4096

///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////



int main(){
  /*tracking_obj* test;
  create_new_tracking_obj(&test);
  printf("%s\n", test->name);
  printf("%d\n", test->flag);
  printf("%d\n", test->perdida);
  printf("-----------------------\n" );
  printf("topleft x:%d\n", test->bounding_box->topleft->x);
  printf("topleft y:%d\n", test->bounding_box->topleft->y);
  printf("bottomright x:%d\n", test->bounding_box->topleft->x);
  printf("bottomright y:%d\n", test->bounding_box->topleft->y);
  printf("-----------------------\n" );


  tracking_obj* zzz;
  create_new_tracking_obj(&zzz);
  zzz->name="luigy";

  tracking_obj* tmp1;
  create_new_tracking_obj(&tmp1);
  
  printf("-----------------------\n" );
  //printf("el primer objeto es : %s \n",test->queue_rectangles);
  printf("-----------------------\n" );




////////////////////////////////////////////////////////
  //implemtar insertar tomando en cuenta el match de overlap
  //implementar funcion limpiar deacuerdo a (perdida=MAX) y recibe el numero de (frame%2)
    //antes de todo revisar el (flag) de acuerdo al frame

  //implementar funcion delete de list para 


  double threshold_rectangle = 0.4;


  Rectangle* myrect1;
  create_myRectangle(&myrect1);
  fill_myRectangle(myrect1, 0,0,10,10);

  Rectangle* myrect2;
  create_myRectangle(&myrect2);
  fill_myRectangle(myrect2, 10,10,20,20);

  Rectangle* myrect3;
  create_myRectangle(&myrect3);
  fill_myRectangle(myrect3, 20,20,30,30);

  Rectangle* myrect4;
  create_myRectangle(&myrect4);
  fill_myRectangle(myrect4, 30,30,40,40);

  Rectangle* myrect5;
  create_myRectangle(&myrect5);
  fill_myRectangle(myrect5, 40,40,50,50);

  Rectangle* myrect6;
  create_myRectangle(&myrect6);
  fill_myRectangle(myrect6, 1,1,11,11);

  Rectangle* myrect7;
  create_myRectangle(&myrect7);
  fill_myRectangle(myrect7, 2,2,12,12);

  int number_frame = 12;

  mylist* l;
  create_mylist(&l);
  my_insert_list_rect2(l, myrect1, threshold_rectangle,number_frame);
  my_insert_list_rect2(l, myrect2, threshold_rectangle,number_frame);
  my_insert_list_rect2(l, myrect3, threshold_rectangle,number_frame);
  my_insert_list_rect2(l, myrect4, threshold_rectangle,number_frame);
  my_insert_list_rect2(l, myrect5, threshold_rectangle,number_frame);
  my_insert_list_rect2(l, myrect6, threshold_rectangle,number_frame);
  my_insert_list_rect2(l, myrect7, threshold_rectangle,number_frame);

  
  l->root->data_obj->perdida=2;
  l->root->next->data_obj->perdida=3;
  l->root->next->next->data_obj->perdida=2;
  l->root->next->next->next->data_obj->perdida=3;
  l->root->next->next->next->next->data_obj->perdida=2;

  printf("%d\n", l->root->data_obj->perdida );
  printf("%d\n", l->root->next->data_obj->perdida);
  printf("%d\n", l->root->next->next->data_obj->perdida);
  printf("%d\n", l->root->next->next->next->data_obj->perdida);
  printf("%d\n", l->root->next->next->next->next->data_obj->perdida);
  limpiar_perdida(l);
  printf("++++++++++++++++++++++\n");
  printf("%d\n", l->root->data_obj->perdida );
  printf("%d\n", l->root->next->data_obj->perdida);
  printf("%d\n", l->root->next->next->data_obj->perdida);
  */
  printf("******************************************\n");
  printf("*****************00000**********************\n");
  
  //char *buffer = (char*)malloc(sizeof(char));
  //char buffer[4096];
  //print_list(l, buffer);
//
  //printf("%s\n", buffer );
  


  //srand(time(NULL));   // should only be called once
  //int r = rand(); 

  FILE *fp;

  fp = fopen( MYFILE , "a");

  
  int i;
  int number_frame = 50;
  mylist* ll;
  double demo_mythreshold_overlap = 0.40;
  create_mylist(&ll);
  int j;

  int max_boundingbox_per_frame = 50;

  for(j=0;j<number_frame;j++)
  {
    char buff[2048];
    fprintf(fp, "///////////////////////\n");
    sprintf(buff,"Frame numero: %d\n",j);
    fprintf(fp, buff);

    for(i=0 ; i<max_boundingbox_per_frame ; i++)
    {
      int left  = rand()%100;
      int right = rand()%100;
      int top   = rand()%100;
      int bot   = rand()%100;

      
      //int zzz = rand()%300;
      //int left  = zzz;
      //int top   = zzz;
      //int right = zzz+10;
      //int bot   = zzz+10;

      Rectangle* myrect_temp;
      create_myRectangle(&myrect_temp);
      fill_myRectangle(myrect_temp,left,top,right,bot);
      //int num_frame = 12;


      my_insert_list_rect2(ll, myrect_temp, demo_mythreshold_overlap, j);
      double temp = buscar_rectangle_returnVeloc(ll,left, right, top, bot);
      printf(">>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>%lf\n",temp );

    }
    printf("update_perdida\n");
    update_perdida_v2(ll, j);
    
    update_distancia(ll);
    update_velocidad(ll);

    printf("limpiar_perdida\n");
    

    limpiar_perdida(ll);
    print_list2(ll,fp);


  }

printf("******************************************\n");
  printf("*******************xxx***********************\n");



  

  fclose(fp);



  printf("******************************************\n");
  printf("*******************zzzz***********************\n");
/*
  Rectangle* myrect33;
  create_myRectangle(&myrect33);
  fill_myRectangle(myrect33, 0,0,10,10);

  Rectangle* myrect44;
  create_myRectangle(&myrect44);
  fill_myRectangle(myrect44, 0,0,5,5);


  double ddd;
  ddd = myoverlap_rectangle(myrect33,myrect44);
  printf("extern - overlap es ddd: %lf \n",ddd);


  float fff;
  fff = my_overlap(*myrect33,*myrect44); 
  printf("extern - overlap es fff: %lf \n",fff);

*/
  return 0;
}
