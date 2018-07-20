#include "mytracking_obj.h"

void myTrackingObj_create(tracking_obj** obj){
  tracking_obj* temp = (tracking_obj*)malloc(sizeof(tracking_obj));
  myTrackingObj_init_create(temp);
  (*obj)=temp;
  return;
}


void myTrackingObj_init_create(tracking_obj* obj){
  obj->name         = VACIOSTRING;
  obj->flagUsed     = 0;
  obj->lostBound    = 0;
  obj->velocidad    = 0;
  obj->distancia    = 0.0;
  obj->pointcenterX = 0;
  obj->pointcenterY = 0;
  obj->rootRect     = NULL;
  obj->queue_rectangles = NULL;

  myRectangle_create( &(obj->rootRect) );
  obj->queue_rectangles = g_queue_new();
  
  return;
}


void myTrackingObj_free(tracking_obj* obj){
  //obj->name         = VACIOSTRING;
  //obj->flagUsed     = 0;
  //obj->lostBound    = 0;
  //obj->velocidad    = 0;
  //obj->distancia    = 0.0;
  //obj->pointcenterX = 0;
  //obj->pointcenterY = 0;
  //obj->rootRect     = NULL;
  //obj->queue_rectangles = NULL;

  //free( obj->name ); //error extranho
  myRectangle_free(obj->rootRect);
  g_queue_free_full(obj->queue_rectangles,&myRectangle_free);
  free( obj );
  obj = NULL;

  return;
}

void myTrackingObj_updateRootRect(tracking_obj* obj, rectangle* rect1){
  if( obj->rootRect == NULL ){
    printf("Error, puntero vacio, rect1.\n");
    return;
  }
  if( rect1 == NULL ){
    printf("Error, puntero vacio, rect2.\n");
    return;
  }

  obj->rootRect->topleft->x     = rect1->topleft->x;
  obj->rootRect->topleft->y     = rect1->topleft->y;
  obj->rootRect->bottomright->x = rect1->bottomright->x;
  obj->rootRect->bottomright->y = rect1->bottomright->y;

  return;
}



void myTrackingObj_addQueue(tracking_obj* obj, rectangle* rect1){
  if( obj->rootRect == NULL ){
    printf("Error, puntero vacio, rect1.\n");
    return;
  }
  if( rect1 == NULL ){
    printf("Error, puntero vacio, rect2.\n");
    return;
  }

  myTrackingObj_updateRootRect(obj,rect1);

  g_queue_push_head(obj->queue_rectangles,rect1);
  myTrackingObj_updateFlagUsed(obj);
  
  int tam_queue = g_queue_get_length(obj->queue_rectangles);
  if(LIMIT_QUEUE<tam_queue)
  {
    rectangle* rect_temp = g_queue_pop_tail(obj->queue_rectangles);
    myRectangle_free(rect_temp);
  }
  return;
}


void myTrackingObj_updateFlagUsed(tracking_obj* obj){
  obj->flagUsed = 1; 
  return;
}


void myTrackingObj_updateAllFlags(GList* mylist){
  int i;
  GList* pfirst = NULL;
  pfirst = g_list_first (mylist);
  while(pfirst)
  {
    if( ((tracking_obj*)(pfirst->data))->flagUsed == 0 )
    {
      ((tracking_obj*)(pfirst->data))->lostBound++;   
    }
    if( ((tracking_obj*)(pfirst->data))->flagUsed == 1 )
    {
      ((tracking_obj*)(pfirst->data))->flagUsed  = 0;   
      ((tracking_obj*)(pfirst->data))->lostBound = 0;
    }
    pfirst = pfirst->next;      
  }  
 
  mylist = g_list_first (mylist);
  return;
}


void myTrackingObj_deleletALLBoundingBoxLost(GList** mylist1){
  if((*mylist1)==NULL){
    printf("Error: lista vacia \n");
    return;
  }

  GList* mylist = NULL;
  mylist = (*mylist1);

  GList* pfirst = NULL;
  mylist = g_list_first(mylist);
  pfirst = mylist;
  
  while(pfirst)
  {
    if( ((tracking_obj*)(pfirst->data))->lostBound >= LIMIT_PERDIDA )
    {
      
      mylist = g_list_remove_link(mylist, pfirst);
      myTrackingObj_free( (tracking_obj*)(pfirst->data));
      pfirst->data = NULL;
      g_list_free_1(pfirst);
      mylist = g_list_first(mylist);
      pfirst=mylist;
    }else{
      pfirst = pfirst->next;
    }
  }
  mylist = g_list_first(mylist);
  (*mylist1)=mylist;
  return;
}

void myTrackingObj_printListObjInFile(GList* mylist, FILE* fp){

  int i;
  
  GList* pfirst = NULL;
  mylist = g_list_first(mylist);
  pfirst = mylist;
  int tam = g_list_length(mylist);
  pfirst = mylist;

  //for(i=0 ; i<tam ; i++){
  while(pfirst){
    char temp[100]  = {0};
    sprintf(temp,"(%i,%i,%i,%i)<<<<<< \n" ,((tracking_obj*)(pfirst->data))->rootRect->topleft->x
                                          ,((tracking_obj*)(pfirst->data))->rootRect->topleft->y
                                          ,((tracking_obj*)(pfirst->data))->rootRect->bottomright->x
                                          ,((tracking_obj*)(pfirst->data))->rootRect->bottomright->y );      
    fprintf(fp, temp);
    myTrackingObj_printTrackingObjInFile((tracking_obj*)(pfirst->data),fp);       
    pfirst = pfirst->next;    
  }
  return;
}


void myTrackingObj_printTrackingObjInFile(tracking_obj* obj, FILE* fp){

  int tam_queue = g_queue_get_length(obj->queue_rectangles);
  int i;

  for(i=0 ; i<tam_queue ; i++){
    char temp[100]  = {0};
    rectangle* myrect = g_queue_peek_nth (obj->queue_rectangles, i );
    sprintf(temp,"      (%i,%i,%i,%i) \n" ,myrect->topleft->x
                                          ,myrect->topleft->y
                                          ,myrect->bottomright->x
                                          ,myrect->bottomright->y );      
    fprintf(fp, temp);
  }
  return;
}




void myTrackingObj_print2(tracking_obj* obj){

  int tam_queue = g_queue_get_length(obj->queue_rectangles);
  int i;

  for(i=0 ; i<tam_queue ; i++){
    rectangle* temp = g_queue_peek_nth (obj->queue_rectangles, i );
    printf("      (%i,%i,%i,%i) \n" ,temp->topleft->x
                                    ,temp->topleft->y
                                    ,temp->bottomright->x
                                    ,temp->bottomright->y );      
  }
  return;
}




void myTrackingObj_print(GList* mylist){
  printf("myTrackingObj_print_locate \n");      

  GList* pfirst = NULL;
  mylist = g_list_first(mylist);
  pfirst = mylist;
  
  int tam1 = g_list_length (pfirst);
  pfirst = mylist;
  
  int g1;
  for (g1=0 ; g1 < tam1 ; g1++)
  {

    ///obj->name         = VACIOSTRING;
    ///obj->flagUsed     = 0;
    ///obj->lostBound    = 0;
    ///obj->velocidad    = 0;
    ///obj->distancia    = 0.0;
    ///obj->pointcenterX = 0;
    ///obj->pointcenterY = 0;
    ///obj->rootRect     = NULL;
    ///obj->queue_rectangles = NULL;

    printf("name         <  %s  > \n",((tracking_obj*)(pfirst->data))->name);
    printf("flagUsed     <  %d  > \n",((tracking_obj*)(pfirst->data))->flagUsed);
    printf("lostBound    <  %d  > \n",((tracking_obj*)(pfirst->data))->lostBound);
    printf("velocidad    <  %lf  > \n",((tracking_obj*)(pfirst->data))->velocidad);
    printf("distancia    <  %lf  > \n",((tracking_obj*)(pfirst->data))->distancia);
    printf("pointcenterX <  %i  > \n",((tracking_obj*)(pfirst->data))->pointcenterX);
    printf("pointcenterY <  %i  > \n",((tracking_obj*)(pfirst->data))->pointcenterY);
    
    printf("(%i,%i,%i,%i) \n" ,((tracking_obj*)(pfirst->data))->rootRect->topleft->x
                              ,((tracking_obj*)(pfirst->data))->rootRect->topleft->y
                              ,((tracking_obj*)(pfirst->data))->rootRect->bottomright->x
                              ,((tracking_obj*)(pfirst->data))->rootRect->bottomright->y );      
    myTrackingObj_print2( (tracking_obj*)(pfirst->data) );
    pfirst = pfirst->next;      
  }
  return;
}



///////////////////////////////////////////////////////
///////////////////////////////////////////////////////



void mytrackingObj_updatePointCenter(tracking_obj* obj, rectangle* rect1){
  if( obj->rootRect == NULL ){
    printf("Error, puntero vacio, rect1.\n");
    return;
  }
  if( rect1 == NULL ){
    printf("Error, puntero vacio, rect2.\n");
    //myRectangle_create(&rect2);
    return;
  }

  obj->pointcenterX = rect1->topleft->x + (rect1->bottomright->x - rect1->topleft->x)/2;
  obj->pointcenterY = rect1->topleft->y + (rect1->bottomright->y - rect1->topleft->y)/2;
  return;
}



void myTrackingObj_updateDistance(tracking_obj* obj)
{
  if(obj==NULL){
    printf("Error: lista vacia, myTrackingObj_updateAllDistances \n");
    return;
  }
  
  rectangle* temp1 = (rectangle*)(obj->queue_rectangles->head->data);
  //printf("    temp1 = %s .\n",temp1);
  rectangle* temp2 = NULL;
  if(obj->queue_rectangles->length <= 2){
    //printf("    cola muy pequenha .\n");
    return; 
  }
  temp2 = (rectangle*)(obj->queue_rectangles->head->next->data);
  obj->distancia += myRectangle_distancia_eu_2rect(temp1,temp2);
  //printf("    obj->distancia = %lf .\n",obj->distancia);
  return;
}


void myTrackingObj_updateSpeed(tracking_obj* obj)
{
  if(obj==NULL){
    printf("Error: lista vacia, myTrackingObj_updateSpeed \n");
    return;
  }
  
  double mytime = (double)obj->queue_rectangles->length;
  double mydist = (double)obj->distancia;
  obj->velocidad = mydist*mytime;
  return;
}




///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


                      //GList* a, rectangle* b
int myfoo_GCompareFunc(void* a, void* b){
  rectangle* p1 = (rectangle*)(((tracking_obj*)(a))->rootRect);
  rectangle* p2 = (rectangle*)(b);
  if( p1 == NULL )
  {
    printf("      Error, puntero vacio, myfoo_GCompareFunc a 1.\n");
    return -1;
  }
  if( p2 == NULL )
  {
    printf("      Error, puntero vacio, myfoo_GCompareFunc b 2.\n");
    return -1;
  }
  
  
  double doubleOverlap = myRectangle_overlap(p1,p2);
//  printf("    doubleOverlap = %lf .\n",doubleOverlap);
  return  (THRESHOLD <= doubleOverlap)?0:-1;
  //if(THRESHOLD <= doubleOverlap)
  //{
  //  return 0;
  //}else{
  //  return -1;
  //}
}






