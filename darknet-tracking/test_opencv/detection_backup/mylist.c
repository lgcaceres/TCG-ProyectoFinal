#include "mylist.h"



void myNodeList_create(mynodelist** n){
  mynodelist* temp = (mynodelist*)malloc(sizeof(mynodelist));
              temp->next     = NULL;
              temp->prev     = NULL;
              temp->data_obj = NULL;
  (*n)=temp;
  return;
}


void myNodeList_free(mynodelist** n){
  (*n)->next = NULL;
  (*n)->prev = NULL;
  //printf("llamado a: myTrackingObj_free\n");
  myTrackingObj_free( &((*n)->data_obj) );
  //printf("llamado a: myTrackingObj_free\n");
  //printf("llamado a: free(*n);11  \n");
  free(*n);  
  //printf("llamado a: free(*n);22  \n");
  (*n) = NULL;
  return;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

/*void create_structure(mylist** l){
  mylist* temp = malloc(sizeof(mylist));
          temp->root = NULL;
  (*l) = temp;
  return;
}*/


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


void myList_create(mylist** l){
  mylist* temp = malloc(sizeof(mylist));
          temp->root = NULL;
  (*l) = temp;
  return;
}

void myList_free(mylist** l){
  if((*l)->root == NULL){
    return;
  }

  mynodelist* temp1 = (*l)->root;
  (*l)->root = NULL;

  while(temp1){
    mynodelist* temp2 = temp1->next;
    myNodeList_free( &(temp1) );
    temp1 = temp2;
  }

  return;
}




void myList_insert_2_rect2(mynodelist* pnode, rectangle* myrect, double threshold_rectangle, int number_frame){
  
  if(threshold_rectangle < myRectangle_myoverlap(pnode->data_obj->bounding_box, myrect)){
    myRectangle_copy(pnode->data_obj->bounding_box, myrect);
    myQueue_enqueue( pnode->data_obj->queue_rectangles, myrect);
    //pnode->data_obj->flag = number_frame % 2;
    pnode->data_obj->flag = 1;
    return;
  }

  if(pnode->next == NULL){
    mynodelist* temp;
    myNodeList_create(&temp);

    tracking_obj* temp_tracking_obj;
    myTrackingObj_create(&temp_tracking_obj);
    temp_tracking_obj->bounding_box = myrect;
    //temp_tracking_obj->flag = number_frame % 2;
    temp_tracking_obj->flag = 1;
    
    temp->data_obj = temp_tracking_obj;
    mytrackingObj_updatePointCenter(temp_tracking_obj, temp_tracking_obj->bounding_box);

    rectangle* myrect_temp = NULL;
    myRectangle_create(&myrect_temp);
    myRectangle_copy(myrect_temp, myrect);
    myQueue_enqueue( temp->data_obj->queue_rectangles, myrect_temp);

    pnode->next = temp;
    temp->prev = pnode;
    return;
  }
  myList_insert_2_rect2(pnode->next, myrect, threshold_rectangle,number_frame);
}



void myList_insert_1_rect2(mylist* l, rectangle* myrect, double threshold_rectangle,int number_frame){

  if(l->root == NULL){
    mynodelist* temp;
                myNodeList_create(&temp);

    tracking_obj* temp_tracking_obj;
                  myTrackingObj_create(&temp_tracking_obj);
                //temp_tracking_obj->flag = number_frame % 2;
                  temp_tracking_obj->flag = 1;
                  temp_tracking_obj->bounding_box = myrect;
                  mytrackingObj_updatePointCenter(temp_tracking_obj, temp_tracking_obj->bounding_box);

    temp->data_obj = temp_tracking_obj;

    //rectangle* myrect_temp = NULL;
    //           myRectangle_create(&myrect_temp);
    //           myRectangle_copy(myrect_temp, myrect);
    //myQueue_enqueue( temp->data_obj->queue_rectangles, myrect_temp );

    myQueue_enqueue( temp->data_obj->queue_rectangles, myrect );
    l->root = temp;
    return;
  }

  myList_insert_2_rect2(l->root, myrect, threshold_rectangle, number_frame);
}





void myList_update_per2(mynodelist* pnode,int number_frame){
  if( pnode->data_obj->flag != (number_frame%2) ){
    ( pnode->data_obj->perdida)++;
  }
  if( pnode->next == NULL){
    return;
  }
  myList_update_per2( pnode->next,number_frame);

}

void myList_update_perdida(mylist* l, int number_frame){
  if(l->root==NULL){
    return;
  }
  myList_update_per2(l->root,number_frame);
}


void myList_update_perdida_v2(mylist* l, int number_frame){
  if(l->root==NULL){
    return;
  }
  mynodelist* temp;
  temp = l->root;
  while(temp){
    if(temp->data_obj->flag == 0){
      (temp->data_obj->perdida)++;   
    }
    if(temp->data_obj->flag == 1){
      temp->data_obj->flag = 0;   
      temp->data_obj->perdida = 0;
    }
    temp = temp->next;
  }
  return;
}


void myList_update_distancia(mylist* l){
  if(l->root==NULL){
    return;
  }

  mynodelist* temp;
  temp = l->root;
  while(temp){
    double distanceTotal = eval_distanceTotal_queue(temp->data_obj->queue_rectangles);
    temp->data_obj->distancia = distanceTotal;
    printf("hola: %lf \n", temp->data_obj->distancia);
    temp = temp->next;
  }

  return;
}


void myList_update_velocidad(mylist* l){
  if(l->root==NULL){
    return;
  }

  mynodelist* temp;
  temp = l->root;
  while(temp){
    if(temp->data_obj->queue_rectangles->limit==0){
      temp->data_obj->velocidad = 0.0;
      printf("------44----------%lf\n", temp->data_obj->velocidad);
    }else{
      temp->data_obj->velocidad = (double)(temp->data_obj->distancia)/(double)(temp->data_obj->queue_rectangles->limit); 
      printf("------55----------%lf\n", temp->data_obj->velocidad);
    }
    temp = temp->next;
  }
  return;
}



//backup myList_limpiar_perdida
/*

void myList_limpiar_perdida(mylist* l){
  if( l->root == NULL ){
    return;
  }

  while(l->root!=NULL && l->root->data_obj->perdida >= LIMIT_PERDIDA  ){
        mynodelist* pnode = l->root;
        l->root = pnode->next;
        l->root->prev = NULL;
        myNodeList_free( &pnode );
        printf("llamado a: myNodeList_free\n");
        free(pnode);
  }
  
  if( l->root == NULL ){
    return;
  }

  
  mynodelist* pnode = l->root;        
  while( pnode->next!=NULL && pnode->next->data_obj->perdida >= LIMIT_PERDIDA ){
        mynodelist** ppnodeAvance = &(pnode->next);
        mynodelist* borrado = pnode->next;
        (*ppnodeAvance) = borrado->next;
        free(borrado);
        pnode = pnode->next;
  }  

  return;

}

*/


void retroceder(mynodelist** pnode){
  while( (*pnode)->prev != NULL ){
    (*pnode) = (*pnode)->prev;
  }
  return;
}



void myList_limpiar_perdida_recursiva_interior(mynodelist** pnode){
    printf("hola00\n");
  if( (*pnode)==NULL ){
    return;
  }

    printf("hola11\n");
  if( (*pnode)->prev==NULL && (*pnode)->next==NULL && (*pnode)->data_obj->perdida >= LIMIT_PERDIDA  ){
    myNodeList_free( pnode );
    printf("llamado a: myNodeList_free11\n");
    free( (*pnode) );
    return;
  }

    printf("hola22\n");
  if( (*pnode)->prev!=NULL && (*pnode)->next==NULL && (*pnode)->data_obj->perdida >= LIMIT_PERDIDA  ){
    mynodelist* temp = (*pnode);
    (*pnode)       = (*pnode)->prev;
    (*pnode)->next = NULL;

    temp->next = NULL;
    temp->prev = NULL;
    myNodeList_free( &temp );
    printf("llamado a: myNodeList_free11\n");
    free( temp );
    return;
  }

    printf("hola33\n");
  if( (*pnode)->prev!=NULL && (*pnode)->next!=NULL && (*pnode)->data_obj->perdida >= LIMIT_PERDIDA  ){
    mynodelist* temp = (*pnode);
    (*pnode)       = (*pnode)->next;
    (*pnode)->prev = temp->prev;

    (*pnode)->prev->next = (*pnode);

    temp->prev = NULL;
    temp->next = NULL;

    myNodeList_free( &temp );
    printf("llamado a: myNodeList_free11\n");
    free(temp);
    myList_limpiar_perdida_recursiva_interior(pnode);
    return;
  }else{
    printf("hola44\n");
    myList_limpiar_perdida_recursiva_interior( &((*pnode)->next) );
  }


}



void myList_limpiar_perdida_recursiva(mylist* l){
  if( l->root == NULL ){
    printf("test0001\n");
    return;
  }
  printf("test00\n");
  mynodelist** pnode = NULL;
  printf("test11\n");
  myList_limpiar_perdida_recursiva_interior(pnode);
  printf("test22\n");
  retroceder(pnode);
  printf("test33\n");
  l->root = (*pnode);
  printf("test44\n");

  return;
}





void myList_limpiar_perdida(mylist* l){
    printf("--------------------\n");
  //printf("myList_limpiar_perdida: 00\n");
  if( l->root == NULL ){
    //printf("myList_limpiar_perdida: 11\n");
    return;
  }
    //printf("myList_limpiar_perdida: 22\n");

  //printf("*11puntero:%s\n",l->root );
  //printf("*22perdida: %d\n",l->root->data_obj->perdida );
  while( (l->root!=NULL) && (l->root->data_obj->perdida >= LIMIT_PERDIDA)  ){
    if(l->root->next == NULL ){
      mynodelist* pnode = l->root;
      //printf("myList_limpiar_perdida: 1-44\n");
      l->root = NULL;
      //printf("myList_limpiar_perdida: 1-55\n");
      //printf("myList_limpiar_perdida: 1-55.1\n");
      myNodeList_free( &pnode );
      //printf("myList_limpiar_perdida: 1-66\n");
      //printf("llamado a: myNodeList_free 1-11\n");
      free(pnode);
      //printf("myList_limpiar_perdida: 1-77\n");
    }else{
      //printf("myList_limpiar_perdida: 2-33\n");
        mynodelist* pnode = l->root;
      //printf("myList_limpiar_perdida: 2-44\n");
        l->root = pnode->next;
      //printf("myList_limpiar_perdida: 2-55\n");
        l->root->prev = NULL;
      //printf("myList_limpiar_perdida: 2-55.1\n");
        myNodeList_free( &pnode );
      //printf("myList_limpiar_perdida: 2-66\n");
        printf("llamado a: myNodeList_free 2-11\n");
      //printf("myList_limpiar_perdida: 2-77\n");
        free(pnode);
    }
  }
  
    //printf("myList_limpiar_perdida: 77\n");
  if( l->root == NULL ){
    printf("myList_limpiar_perdida: 77\n");
    return;
  }

    //printf("myList_limpiar_perdida: 88\n");
  mynodelist* pnode = l->root;        
  //printf("*55puntero:%s\n",pnode->next );
  //printf("*66perdida: %d\n",pnode->next->data_obj->perdida );
  while( pnode->next!=NULL ){
    //printf("myList_limpiar_perdida: 99\n");
    if( pnode->next->next==NULL && pnode->next->data_obj->perdida >= LIMIT_PERDIDA){
    //printf("myList_limpiar_perdida: 1010\n");
      mynodelist* borrado = pnode->next;
      borrado->next = NULL;
      borrado->prev = NULL;

      pnode->next = NULL;
      myNodeList_free( &borrado );
      printf("llamado a: myNodeList_free22\n");
      free(borrado);
      break;
    }
    //printf("myList_limpiar_perdida: 1111\n");


    if( pnode->next->next!=NULL && pnode->next->data_obj->perdida >= LIMIT_PERDIDA ){
    //printf("myList_limpiar_perdida: 1212\n");
      mynodelist* temp1 = pnode->next;
      mynodelist* temp2 = pnode->next->next;

      temp2->prev = pnode;
      pnode->next = temp2;

      temp1->next = NULL;
      temp1->prev = NULL;
      myNodeList_free( &temp1 );
      printf("llamado a: myNodeList_free33\n");
      free(temp1);
    }else{
    //printf("myList_limpiar_perdida: 1313\n");
      //printf("llamado a: paso sin ver\n");
      pnode = pnode->next;
    }
  }  

    //printf("myList_limpiar_perdida: 1414\n");
  //printf("la cague\n");
    printf("--------------------\n");

  return;
}





//void myList_print(mylist* l, char buffer[SIZEOF_BUFF], FILE* fp){
void myList_print(mylist* l, FILE* fp){
  mynodelist* ptemp = l->root;
  int i=0;

  while(ptemp){
    rectangle* temp_boundingbox = ptemp->data_obj->bounding_box;

    char temp[100]  = {0};
    //sprintf(temp, ", val%d", k);
    sprintf(temp,"list-(%d): (%d,%d) (%d,%d)\n", i
                              ,temp_boundingbox->topleft->x 
                              ,temp_boundingbox->topleft->y
                              ,temp_boundingbox->bottomright->x
                              ,temp_boundingbox->bottomright->y );
    fprintf(fp, temp);
    //print_queue_rectagles(ptemp->data_obj->queue_rectangles, temp, fp);  
    print_queue_rectagles(ptemp->data_obj->queue_rectangles, fp);  
    //strcat(buffer, temp);

    //char buff[2048];
    //fprintf(fp, "///////////////////////\n");
    //sprintf(buff,"Frame numero: %d\n",number_frame);
    //print_queue_rectagles(ptemp->data_obj->queue_rectangles, buffer);
    ptemp = ptemp->next;
    i++;
  }

  return;
}



void myList_print2(mylist* l, FILE* fp){
  mynodelist* ptemp = l->root;
  int i=0;

  while(ptemp){
    rectangle* temp_boundingbox = ptemp->data_obj->bounding_box;

    char temp[100]  = {0};
    
    //char *name;
    //int flag; //0-1
    //int perdida; //maximo 10

    sprintf(temp,"list-(%d): [%d,%d] (%s) (perdida:%d)", i
                              ,ptemp->data_obj->pointcenterX
                              ,ptemp->data_obj->pointcenterY
                              ,ptemp->data_obj->name
                              ,ptemp->data_obj->perdida);
    fprintf(fp, temp);

    sprintf(temp," : (%d,%d) (%d,%d)\n"
                              ,temp_boundingbox->topleft->x 
                              ,temp_boundingbox->topleft->y
                              ,temp_boundingbox->bottomright->x
                              ,temp_boundingbox->bottomright->y );
    fprintf(fp, temp);
    //print_queue_rectagles(ptemp->data_obj->queue_rectangles, temp, fp);  
    print_queue_rectagles(ptemp->data_obj->queue_rectangles, fp);  
    sprintf(temp,"\n");
    fprintf(fp, temp);
    //strcat(buffer, temp);

    //char buff[2048];
    //fprintf(fp, "///////////////////////\n");
    //sprintf(buff,"Frame numero: %d\n",number_frame);
    //print_queue_rectagles(ptemp->data_obj->queue_rectangles, buffer);
    ptemp = ptemp->next;
    i++;
  }

  return;
}



double myList_buscar_rectangle_returnDistance(mylist* l, int left, int right, int top, int bot){
  
  mynodelist* ptemp = l->root;

  double distance_result = 0.0;


  while(ptemp){
    rectangle* temp_boundingbox = ptemp->data_obj->bounding_box;
    if(temp_boundingbox->topleft->x     == left  &&
       temp_boundingbox->topleft->y     == top   &&
       temp_boundingbox->bottomright->x == right   &&
       temp_boundingbox->bottomright->y == bot   ){
      distance_result = ptemp->data_obj->distancia;
      //printf("entreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee11\n");
      //printf("entreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee22\n");
      break;
    }
    ptemp = ptemp->next;
  }
  if(distance_result==0.0){
    //printf("ptm!!!!!!!!!!!!!!!!!!!\n");
  }
  
  return distance_result;
}


double myList_buscar_rectangle_returnVeloc(mylist* l, int left, int right, int top, int bot){
  
  mynodelist* ptemp = l->root;

  double velocidad_result = 0.0;


  while(ptemp){
    rectangle* temp_boundingbox = ptemp->data_obj->bounding_box;
    if(temp_boundingbox->topleft->x     == left  &&
       temp_boundingbox->topleft->y     == top   &&
       temp_boundingbox->bottomright->x == right   &&
       temp_boundingbox->bottomright->y == bot   ){
      velocidad_result = ptemp->data_obj->velocidad;
      //printf("entreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee11\n");
      //printf("entreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee22\n");
      break;
    }
    ptemp = ptemp->next;
  }
  if(velocidad_result==0.0){
    //printf("ptm!!!!!!!!!!!!!!!!!!!\n");
  }
  
  return velocidad_result;
}



/*
void myList_limpiar_perdida(mylist* l){
  
  if( l->root == NULL ){
    printf("borrando2\n");
    return;
  }
  while(l->root!=NULL && l->root->data_obj->perdida >= LIMIT_PERDIDA  ){
        mynodelist* pnode = l->root;
        l->root = pnode->next;
        free(pnode);
        printf("borrando4\n");
  }
        printf("AAAAAAAAAAAAAAAAA\n");
  
  if( l->root == NULL ){
    printf("borrando5\n");
    return;
  }

  
  mynodelist* pnode = l->root;
        printf("AAAAAAAAAAAAAAAAA<<<<1\n");
  while( pnode->next->data_obj->perdida >= LIMIT_PERDIDA ){
        printf("AAAAAAAAAAAAAAAAA<<<<2\n");
        mynodelist** ppnodeAvance = &(pnode->next);
        mynodelist* borrado = pnode->next;
        (*ppnodeAvance) = borrado->next;
        free(borrado);
        printf("borrando6\n");
        pnode = pnode->next;
  }  
          printf("bbbbbbbbbbbbbbbb\n");

  return;

}


*/




/*
void my_insert_list2(mynodelist* pnode, mynodelist* temp){
  if(pnode->next == NULL){
     pnode->next = temp;
    return;
  }
  my_insert_list2(pnode->next,temp);
}

void my_insert_list(mylist* l, tracking_obj* pdato){
  mynodelist* temp;
  myNodeList_create(&temp);
  temp->data_obj=pdato;
  if(l->root == NULL){
    l->root = temp;
    return;
  }
  my_insert_list2(l->root,temp);
}
*/







//void my_delete_list(mylist* l, tracking_obj* pdato){
//  mynodelist* temp = (mynodelist*)malloc(sizeof(mynodelist));
//    temp->data_obj = pdato;
//    temp->next = NULL;
//    temp->prev = NULL;
//  if(l->root == NULL){
//    l->root = temp;
//    return;
//  }
//  my_insert_list2(l->root,temp);
//}
