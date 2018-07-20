

#include "mytracking_obj.h"




void free_new_tracking_obj(tracking_obj** obj){
  //printf("llamando a: free_myRectangle\n");
  //free_myRectangle( &((*obj)->bounding_box) );
  free((*obj)->bounding_box);

  //printf("llamando a: free_queue1\n");
  free_queue(&((*obj)->queue_rectangles));
 // printf("llamando a: free_queue2\n");
  
  //printf("llamando a: free((*obj)->name);11\n");
  //free((*obj)->name);
  //printf("llamando a: free((*obj)->name);22\n");

  //printf("llamando a: free((*obj));11\n");
  free((*obj));
 // printf("llamando a: free((*obj));22\n");
  (*obj) = NULL;
  return;
}




void create_new_tracking_obj(tracking_obj** obj){
  tracking_obj* temp = (tracking_obj*)malloc(sizeof(tracking_obj));
                temp->name = VACIOSTRING;
                temp->flag = 0;
                temp->perdida = 0;

                temp->velocidad = 0;
                temp->distancia = 0.0;

                temp->pointcenterX = 0;
                temp->pointcenterY = 0;

                temp->bounding_box = NULL;
                create_myRectangle(&(temp->bounding_box));
                temp->queue_rectangles = NULL;
                create_queue(&temp->queue_rectangles);
  (*obj)=temp;
  return;
}


void update_tracking_obj(tracking_obj* obj, Rectangle* rect1){
  if( obj->bounding_box == NULL ){
    printf("Error, puntero vacio, rect1.\n");
    return;
  }
  if( rect1 == NULL ){
    printf("Error, puntero vacio, rect2.\n");
    //create_myRectangle(&rect2);
    return;
  }

  obj->bounding_box->topleft.x     = rect1->topleft.x;
  obj->bounding_box->topleft.y     = rect1->topleft.y;
  obj->bounding_box->bottomright.x = rect1->bottomright.x;
  obj->bounding_box->bottomright.y = rect1->bottomright.y;

  return;
}



void update_pointCenter(tracking_obj* obj, Rectangle* rect1){
  if( obj->bounding_box == NULL ){
    printf("Error, puntero vacio, rect1.\n");
    return;
  }
  if( rect1 == NULL ){
    printf("Error, puntero vacio, rect2.\n");
    //create_myRectangle(&rect2);
    return;
  }


  obj->pointcenterX = rect1->topleft.x + (rect1->bottomright.x - rect1->topleft.x)/2;
  obj->pointcenterY = rect1->topleft.y + (rect1->bottomright.y - rect1->topleft.y)/2;
  return;
}


double distancia_eu_2rect(Rectangle* rect1, Rectangle* rect2){
  if( rect1 == NULL ){
    printf("Error, puntero vacio, rect1.\n");
    //create_myRectangle(&rect2);
    return -1.0;
  }

  if( rect2 == NULL ){
    printf("Error, puntero vacio, rect2.\n");
    //create_myRectangle(&rect2);
    return -1.0;
  }

  int x1 = rect1->topleft.x + (rect1->bottomright.x - rect1->topleft.x)/2;
  int y1 = rect1->topleft.y + (rect1->bottomright.y - rect1->topleft.y)/2;

  int x2 = rect2->topleft.x + (rect2->bottomright.x - rect2->topleft.x)/2;
  int y2 = rect2->topleft.y + (rect2->bottomright.y - rect2->topleft.y)/2;

  double dist = sqrt( pow(x1-x2,2) + pow(y1-y2,2) );

  return dist;
}

