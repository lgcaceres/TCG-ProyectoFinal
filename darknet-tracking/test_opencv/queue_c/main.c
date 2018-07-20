
#include<stdio.h>
#include<stdlib.h>



struct mynode{
  int data;
  struct mynode* next;
};

typedef struct mynode mynode;


typedef struct{
  mynode* front;
  mynode* rear;
}queue;



void create_queue(queue** myqueue){
    queue* temp=malloc(sizeof(queue));
    temp->front=NULL;
    temp->rear=NULL;
    *myqueue = temp;
    return;
}



void enqueue(queue* myqueue, int x){
  mynode* temp = (mynode*)malloc(sizeof(mynode));
  temp->data = x; 
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



int front(queue* myqueue){
  if(myqueue->front == NULL) {
    printf("Queue is empty\n");
    return;
  }
  return myqueue->front->data;
}

void print(queue* myqueue) {
  mynode* temp = myqueue->front;
  while(temp != NULL) {
    printf("%d ",temp->data);
    temp = temp->next;
  }
  printf("\n");
}

int main(){

  queue* myqueue;
  create_queue(&myqueue);
  enqueue(myqueue,2); 
  print(myqueue); 
  enqueue(myqueue,4); 
  print(myqueue);
  enqueue(myqueue,6); 
  print(myqueue);
  dequeue(myqueue);  
  print(myqueue);

}
