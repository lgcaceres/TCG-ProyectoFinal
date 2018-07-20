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
  obj->distanceTotal    = 0.0;
  obj->distanceCurr    = 0.0;
  obj->pointcenterX = 0;
  obj->pointcenterY = 0;
  obj->rootRect     = NULL;
  obj->queue_rectangles = NULL;
  obj->isPoint      = 0;
  myRectangle_create( &(obj->rootRect) );
  obj->queue_rectangles = g_queue_new();
  
  return;
}


void myTrackingObj_free(tracking_obj* obj){
  //obj->name         = VACIOSTRING;
  //obj->flagUsed     = 0;
  //obj->lostBound    = 0;
  //obj->velocidad    = 0;
  //obj->distanceTotal    = 0.0;
  //obj->distanceCurr    = 0.0;
  //obj->pointcenterX = 0;
  //obj->pointcenterY = 0;
  //obj->rootRect     = NULL;
  //obj->queue_rectangles = NULL;

  free( obj->name ); //error extranho
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


  
  int _isPoint = myRectangle_isPoint(rect1);
  if(_isPoint == -1){
    printf(" update point\n");
    obj->isPoint=_isPoint;
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
  printf("    myTrackingObj_updateAllFlags 11\n");
  int i;
  GList* pfirst = NULL;
  pfirst = g_list_first (mylist);
  printf("    myTrackingObj_updateAllFlags 12\n");
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
 
  printf("    myTrackingObj_updateAllFlags 13\n");
  mylist = g_list_first (mylist);
  printf("    myTrackingObj_updateAllFlags 14\n");
  return;
}


void myTrackingObj_deleteALLBoundingBoxLost(GList** mylist1){
  if((*mylist1)==NULL){
    printf("Error: lista vacia \n");
    return;
  }

  //GList* mylist = NULL;
  //mylist = (*mylist1);

  (*mylist1) = g_list_first(*mylist1);

  GList* pfirst = NULL;
  pfirst = *mylist1;
  
  while(pfirst)
  {
    //if( ((tracking_obj*)(pfirst->data))->isPoint==-1 || ((tracking_obj*)(pfirst->data))->lostBound >= LIMIT_PERDIDA )
    if( ((tracking_obj*)(pfirst->data))->lostBound >= LIMIT_PERDIDA )
    {
      *mylist1 = g_list_remove_link(*mylist1, pfirst);

      //myTrackingObj_free( (tracking_obj*)(pfirst->data)); /// corregir <<<<<<<<<<<<<<<<<<
      //pfirst->data = NULL;                              /// corregir <<<<<<<<<<<<<<<<<<
      //g_list_free(pfirst);                              /// corregir <<<<<<<<<<<<<<<<<<
      
      *mylist1 = g_list_first(*mylist1);
      pfirst=*mylist1;
    }else{
      pfirst = pfirst->next;
    }
  }
  *mylist1 = g_list_first(*mylist1);
  //(*mylist1)=mylist;
  return;
}

void myTrackingObj_printListObjInFile(GList* mylist, FILE* fp){

  
  fprintf(fp, "/////////////////////myTrackingObj_printListObjInFile////////////////////////////11\n");
  mylist = g_list_first(mylist);

  GList* pfirst = NULL;
  pfirst = mylist;
  int tam = g_list_length(pfirst);
  pfirst = mylist;

  int i=0;
  while(pfirst)
  {
    char temp[300]  = {0};
    //int   flagUsed; //0-1
    //int   lostBound; //maximo 10
    //double velocidad;
    //double distanceTotal;
    //int pointcenterX;
    //int pointcenterY;
    fprintf(fp, temp);

    sprintf(temp,"flagUsed:%i \n,lostBound:%i \n,velocidad:%lf \n,distanceTotal:%lf \n,distanceCurr:%lf \n,isPoint = %i\n"
                  ,((tracking_obj*)(pfirst->data))->flagUsed
                  ,((tracking_obj*)(pfirst->data))->lostBound
                  ,((tracking_obj*)(pfirst->data))->velocidad
                  ,((tracking_obj*)(pfirst->data))->distanceTotal
                  ,((tracking_obj*)(pfirst->data))->distanceCurr
                  ,((tracking_obj*)(pfirst->data))->isPoint);      
    fprintf(fp, temp);

    sprintf(temp,"(%i,%i,%i,%i)<<%i>> \n" ,((tracking_obj*)(pfirst->data))->rootRect->topleft->x
                                          ,((tracking_obj*)(pfirst->data))->rootRect->topleft->y
                                          ,((tracking_obj*)(pfirst->data))->rootRect->bottomright->x
                                          ,((tracking_obj*)(pfirst->data))->rootRect->bottomright->y
                                          ,i );      
    fprintf(fp, temp);

    myTrackingObj_printTrackingObjInFile((tracking_obj*)(pfirst->data),fp);       
    pfirst = pfirst->next;    
    i++;
  }
  fprintf(fp, "/////////////////////myTrackingObj_printListObjInFile////////////////////////////12\n");
  return;
}


void myTrackingObj_printListObjInFile_points(GList* mylist, FILE* fp){

  
  mylist = g_list_first(mylist);

  GList* pfirst = NULL;
  pfirst = mylist;
  int tam = g_list_length(pfirst);
  pfirst = mylist;

  int i=0;
  while(pfirst)
  {
    char temp[300]  = {0};
    //int   flagUsed; //0-1
    //int   lostBound; //maximo 10
    //double velocidad;
    //double distanceTotal;
    //int pointcenterX;
    //int pointcenterY;
    int xx =0;
    int xx_min = ((tracking_obj*)(pfirst->data))->rootRect->topleft->x > ((tracking_obj*)(pfirst->data))->rootRect->bottomright->x ? ((tracking_obj*)(pfirst->data))->rootRect->bottomright->x  : ((tracking_obj*)(pfirst->data))->rootRect->bottomright->x;
    int xx_max = ((tracking_obj*)(pfirst->data))->rootRect->topleft->x < ((tracking_obj*)(pfirst->data))->rootRect->bottomright->x ? ((tracking_obj*)(pfirst->data))->rootRect->topleft->x      : ((tracking_obj*)(pfirst->data))->rootRect->topleft->x;
        xx = xx_max-xx_min;
        xx = xx/2 + xx_min;

    int yy =0;
    int yy_min = ((tracking_obj*)(pfirst->data))->rootRect->topleft->y > ((tracking_obj*)(pfirst->data))->rootRect->bottomright->y ? ((tracking_obj*)(pfirst->data))->rootRect->bottomright->y : ((tracking_obj*)(pfirst->data))->rootRect->bottomright->y;
    int yy_max = ((tracking_obj*)(pfirst->data))->rootRect->topleft->y < ((tracking_obj*)(pfirst->data))->rootRect->bottomright->y ? ((tracking_obj*)(pfirst->data))->rootRect->topleft->y     : ((tracking_obj*)(pfirst->data))->rootRect->topleft->y;
        yy = yy_max-yy_min;
        yy = yy/2 + yy_min;


    sprintf(temp,"%i %i \n",xx,yy);      
    fprintf(fp, temp);

    pfirst = pfirst->next;    
    i++;
  }
  
  return;
}




void myTrackingObj_printTrackingObjInFile(tracking_obj* obj, FILE* fp){

  int tam_queue = g_queue_get_length(obj->queue_rectangles);
  int i;

  for(i=0 ; i<tam_queue ; i++){
    char temp[100]  = {0};
    rectangle* myrect = g_queue_peek_nth (obj->queue_rectangles, i );
    sprintf(temp,"      (%i,%i,%i,%i) <<%i>>\n" ,myrect->topleft->x
                                                ,myrect->topleft->y
                                                ,myrect->bottomright->x
                                                ,myrect->bottomright->y
                                                ,i );      
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
    ///obj->distanceTotal    = 0.0;
    ///obj->pointcenterX = 0;
    ///obj->pointcenterY = 0;
    ///obj->rootRect     = NULL;
    ///obj->queue_rectangles = NULL;

    printf("name         <%s>  \n",((tracking_obj*)(pfirst->data))->name);
    printf("flagUsed     <%d>  \n",((tracking_obj*)(pfirst->data))->flagUsed);
    printf("lostBound    <%d>  \n",((tracking_obj*)(pfirst->data))->lostBound);
    printf("velocidad    <%lf> \n",((tracking_obj*)(pfirst->data))->velocidad);
    printf("distanceTotal<%lf> \n",((tracking_obj*)(pfirst->data))->distanceTotal);
    printf("distanceCurr <%lf> \n",((tracking_obj*)(pfirst->data))->distanceTotal);
    printf("pointcenterX <%i>  \n",((tracking_obj*)(pfirst->data))->pointcenterX);
    printf("pointcenterY <%i>  \n",((tracking_obj*)(pfirst->data))->pointcenterY);
    
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
  rectangle* temp2 = NULL;
  if(obj->queue_rectangles->length < 2){
    return; 
  }
  temp2 = (rectangle*)(obj->queue_rectangles->head->next->data);
  obj->distanceCurr   = myRectangle_distancia_eu_2rect(temp1,temp2);
  obj->distanceTotal += obj->distanceCurr;
  //printf("    obj->distanceTotal = %lf .\n",obj->distanceTotal);
  return;
}


void myTrackingObj_updateSpeed(tracking_obj* obj)
{
  if(obj==NULL){
    printf("Error: lista vacia, myTrackingObj_updateSpeed \n");
    return;
  }
  
  rectangle* temp1 = (rectangle*)(obj->queue_rectangles->head->data);
  rectangle* temp2 = NULL;
  if(obj->queue_rectangles->length < 2){
    return; 
  }
  temp2 = (rectangle*)(obj->queue_rectangles->head->next->data);

  
  //double mytime = (double)obj->queue_rectangles->length;
  //double mydist = (double)obj->distanceTotal;
  //obj->velocidad = mydist/mytime;
  //XXXXXXXXXXXXXXXXX
  obj->velocidad =  myTrackingObj_averageVelocity(temp1,temp2,0,1);
  
  return;
}


//velocidad media
double myTrackingObj_averageVelocity(rectangle* rectO, rectangle* rectF, int timeO, int timeF){
  double deltaPos  = myRectangle_distancia_eu_2rect(rectO,rectF); 
  double deltaTime = timeF-timeO;
  return deltaPos/deltaTime;
}




///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


                      //GList* a, rectangle* b
int myfoo_GCompareFunc(void* a, void* b){
  printf("        myfoo_GCompareFunc");
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
  printf("    doubleOverlap = %lf .\n",doubleOverlap);
  //return  (THRESHOLD_IOU <= doubleOverlap)?0:-1;
  if(THRESHOLD_IOU <= doubleOverlap)
  {
    return 0;
  }else{
    return -1;
  }
}





void myTrackingObj_printListObjInFile_velocity(GList* mylist, FILE* fp){

  
  mylist = g_list_first(mylist);

  GList* pfirst = NULL;
  pfirst = mylist;
  int tam = g_list_length(pfirst);
  pfirst = mylist;

  int i=0;
  while(pfirst)
  {
    char temp[300]  = {0};
    //int   flagUsed; //0-1
    //int   lostBound; //maximo 10
    //double velocidad;
    //double distanceTotal;
    //int pointcenterX;
    //int pointcenterY;
    fprintf(fp, temp);

    sprintf(temp,"%lf \n",((tracking_obj*)(pfirst->data))->velocidad);      
    fprintf(fp, temp);

    fprintf(fp, temp);

    pfirst = pfirst->next;    
    i++;
  }
  return;
}


void myTrackingObj_printListObjInFile_anomalusORnot(GList* mylist, FILE* fp, char* demo_basename_filename, double velocity)
{



  mylist = g_list_first(mylist);

  GList* pfirst = NULL;
  pfirst = mylist;
  int tam = g_list_length(pfirst);
  pfirst = mylist;


    char temp[300]  = {0};
    if(velocity >= (THRESHOLD_VELOCITY+DESV_DESVIACION_VELOCITY) ){
      //sprintf(temp,"%s,%s \n",demo_basename_filename,"anomalo");      
      sprintf(temp,"%s,%d \n",demo_basename_filename,1);      
      fprintf(fp, temp);
    }else{
      sprintf(temp,"%s,%d \n",demo_basename_filename,0);      
      //sprintf(temp,"%s,%s \n",demo_basename_filename,"no anomalo");      
      fprintf(fp, temp);
    }
  
            
  /*int i=0;
  while(pfirst)
  {
    char temp[300]  = {0};
    if(velocity >= (THRESHOLD_VELOCITY+DESV_DESVIACION_VELOCITY) ){
      sprintf(temp,"%s,%d \n",demo_basename_filename,1);      
      fprintf(fp, temp);
    }else{
      sprintf(temp,"%s,%d \n",demo_basename_filename,0);      
      fprintf(fp, temp);
    }  

    pfirst = pfirst->next;    
    i++;
  }
  return;
  */

  return;
}
