#include "myqueue.h"


void create_mynode_queue(mynode** pnode){
 mynode* temp = (mynode*)malloc(sizeof(mynode));
         temp->data_rect = NULL; 
         temp->next = NULL;
 (*pnode) = temp;
 return;
}

void free_mynode_queue(mynode** pnode){
  //printf("dentro de free_mynode_queue11\n");
  //free_myRectangle( &((*pnode)->data_rect) );
  free( &((*pnode)->data_rect) );
  //printf("dentro de free_mynode_queue22\n");
  (*pnode)->next = NULL;
  //printf("dentro de free_mynode_queue33\n");
  //free( *pnode );
  //printf("dentro de free_mynode_queue44\n");
  //return;
}




///////////////////////////////////////////////////
///////////////////////////////////////////////////


void create_queue(queue** myqueue){
    queue* temp=malloc(sizeof(queue));
           temp->front=NULL;
           temp->rear=NULL;
           temp->limit=0;
    *myqueue = temp;
    return;
}


void free_queue(queue** myqueue){
  while( (*myqueue)->front ){
    //printf("llamando dentro de while de: dequeue_rectangle11 \n");
    dequeue_rectangle( *myqueue );
    //printf("llamando dentro de while de: dequeue_rectangle22 \n");
  }
  free( *myqueue );
  return;
}




void enqueue_rectangle(queue* myqueue, Rectangle* rect){
  mynode* temp = NULL;
  create_mynode_queue(&temp);
  temp->data_rect = rect; 

  if(myqueue->front == NULL && myqueue->rear == NULL){
    myqueue->front = myqueue->rear = temp;
    myqueue->limit++;
    return;
  }
  if( myqueue->limit > LIMIT_QUEUE ){
      dequeue_rectangle(myqueue);
      //cola llena
      //printf("borrando \n");
  }
  myqueue->rear->next = temp;
  myqueue->rear = temp;
  myqueue->limit++;
  return;
}


void dequeue_rectangle(queue* myqueue) {
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
  
  //printf("llamando a: free_mynode_queue11\n");
  free_mynode_queue( &temp );
  //printf("llamando a: free_mynode_queue22\n");

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
    Rectangle* tempRect1 = tempFront->data_rect;
    if(tempFront->next==NULL){
      break;
    }
    if(tempFront->next!=NULL){
      Rectangle* tempRect2 = tempFront->next->data_rect;
      distanceTotal = distanceTotal + distancia_eu_2rect(tempRect1, tempRect2);
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
                                      ,temp_rect->data_rect->topleft.x 
                                      ,temp_rect->data_rect->topleft.y
                                      ,temp_rect->data_rect->bottomright.x
                                      ,temp_rect->data_rect->bottomright.y ); 
    //strcat(buffer, temp);
    fprintf(fp, temp);

    temp_rect = temp_rect->next;
    i++;
  }
  return;
}





/*

void enqueue(queue* myqueue, int x){
  mynode* temp = (mynode*)malloc(sizeof(mynode));
  //temp->data = x; 
  temp->next = NULL;
  if(myqueue->front == NULL && myqueue->rear == NULL){
    myqueue->front = myqueue->rear = temp;
    return;
  }
  myqueue->rear->next = temp;
  myqueue->rear = temp;
}


void dequeue(queue* myqueue) {
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
  free(temp);
}

*/