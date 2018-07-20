#include "myqueue.h"


void myNodeQueue_create(mynode** pnode){
 mynode* temp = (mynode*)malloc(sizeof(mynode));
         temp->data_rect = NULL; 
         temp->next      = NULL;
 (*pnode) = temp;
 return;
}

void myNodeQueue_free(mynode** pnode){

  myRectangle_free(&((*pnode)->data_rect));

  (*pnode)->next = NULL;

  return;
}




///////////////////////////////////////////////////
///////////////////////////////////////////////////


void myQueue_create(queue** myqueue){
    queue* temp = malloc(sizeof(queue));
           temp->front = NULL;
           temp->rear  = NULL;
           temp->limit = 0;
    (*myqueue) = temp;
    return;
}


void myQuee_free(queue** myqueue){
  while( (*myqueue)->front ){
    //printf("llamando dentro de while de: myQueue_dequeue \n");
    myQueue_dequeue( *myqueue );
    //printf("llamando dentro de while de: myQueue_dequeue \n");
  }
  free( *myqueue );
  (*myqueue) = NULL;
  return;
}





void myQueue_enqueue(queue* myqueue, rectangle* rect){
  mynode* temp = NULL;
  myNodeQueue_create(&temp);
  temp->data_rect = rect; 

  if(myqueue->front == NULL && myqueue->rear == NULL){
    myqueue->front = myqueue->rear = temp;
    myqueue->limit++;
    return;
  }
  if( myqueue->limit > LIMIT_QUEUE ){
      myQueue_dequeue(myqueue);
      //cola llena
      //printf("borrando \n");
  }
  myqueue->rear->next = temp;
  myqueue->rear = temp;
  myqueue->limit++;
  return;
}


void myQueue_dequeue(queue* myqueue) {
  mynode* temp = myqueue->front;
  if(myqueue->front == NULL){
    printf("Queue is Empty\n");
    return;
  }
  if(myqueue->front == myqueue->rear){
    myqueue->front = myqueue->rear = NULL;
  }else{
    myqueue->front = myqueue->front->next;
  }
  
  myNodeQueue_free( &temp );
 
  myqueue->limit--;
  return;
}



double eval_distanceTotal_queue(queue* myqueue){
  mynode* tempFront = myqueue->front;
  double distanceTotal = 0.0; 

  if(tempFront == NULL){
    printf("Queue is Empty\n");
    return distanceTotal;
  }

  while(tempFront!=NULL){
    rectangle* tempRect1 = tempFront->data_rect;
    if(tempFront->next==NULL){
      break;
    }
    if(tempFront->next!=NULL){
      rectangle* tempRect2 = tempFront->next->data_rect;
      distanceTotal = distanceTotal + myTrackingObj_distancia_eu_2rect(tempRect1, tempRect2);
      tempFront = tempFront->next;
    }
  }
  return distanceTotal;
}






//void print_queue_rectagles(queue* myqueue, char buffer[SIZEOF_BUFF],FILE* fp)
void print_queue_rectagles(queue* myqueue,FILE* fp)
{
  mynode* temp_rect = myqueue->front;
  int i = 0;
  while(temp_rect){
    char temp[100]  = {0};
    sprintf(temp,"     cola-(%d): (%d,%d) (%d,%d)\n", i
                                      ,temp_rect->data_rect->topleft->x 
                                      ,temp_rect->data_rect->topleft->y
                                      ,temp_rect->data_rect->bottomright->x
                                      ,temp_rect->data_rect->bottomright->y ); 
    //strcat(buffer, temp);
    fprintf(fp, temp);

    temp_rect = temp_rect->next;
    i++;
  }
  return;
}


