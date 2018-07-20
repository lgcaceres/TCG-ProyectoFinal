
#include <stdio.h>
#include <math.h>
#include <string.h>



#include <time.h>
#include <stdlib.h>


#include "mycommon.h"
#include <gmodule.h>


//#define SIZEOF_BUFF 4096

///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////



int main(){

  printf("&&&&&&&&&&&&&&&&&00000000&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
  FILE *fp;

  fp = fopen( MYFILE , "a");
 
  int i;
  int j;

  //int number_frame = 2;
  //int max_boundingbox_per_frame = 2;

  int number_frame = 200;
  int max_boundingbox_per_frame = 200;
  
  //create_structure(&ll);
  //mylist* ll;
  //myList_create(&ll);

  GList * mylist = NULL;

  srand(time(0));
  for(j=0 ; j<number_frame ; j++)
  {
    printf("88888888888888888888888888888888888888888888888 for principal inicio %d \n", j);
    char buff[2048];
    fprintf(fp, "///////////////////////\n");
    sprintf(buff,"Frame numero: %d\n",j);
    fprintf(fp, buff);

    for(i=0 ; i<max_boundingbox_per_frame ; i++)
    {
    printf("    88888888888888888888888888888888888888888888888 for secundario inicio %d \n",i);
      int top   = rand()%30;
      int left  = rand()%30;
      int bot   = rand()%30;
      int right = rand()%30;

      //int top   = rand()%30;
      //int left  = rand()%30;
      //int bot   = top+10;
      //int right = left+10;

      rectangle* myrect_temp;
      myRectangle_create( &myrect_temp );
      myRectangle_fill(myrect_temp, left, top, right, bot);

      GList* pGlist = NULL;
      if( mylist==NULL)
      {
        tracking_obj* mytrack_temp = NULL;
        myTrackingObj_create(&mytrack_temp);
        myTrackingObj_init_create(mytrack_temp);
        myTrackingObj_addQueue(mytrack_temp,myrect_temp);
        mytrackingObj_updatePointCenter(mytrack_temp,myrect_temp);
        myTrackingObj_updateDistance(mytrack_temp);
        myTrackingObj_updateSpeed(mytrack_temp);
        mylist = g_list_prepend(mylist,mytrack_temp);
        //mylist = g_list_first(mylist);//ya es primero
        //myTrackingObj_print(mylist);

      }else{
        mylist = g_list_first(mylist);//reseteando pos
        pGlist = mylist;
        pGlist = g_list_find_custom(pGlist, myrect_temp, &myfoo_GCompareFunc);
        if( pGlist != NULL )
        {
          myTrackingObj_addQueue((tracking_obj*)(pGlist->data),myrect_temp);
          mytrackingObj_updatePointCenter((tracking_obj*)(pGlist->data),myrect_temp);
          tracking_obj* temp = (tracking_obj*)(pGlist->data);
          myTrackingObj_updateDistance(temp);
          myTrackingObj_updateSpeed(temp);
        }else{
          tracking_obj* mytrack_temp = NULL;
          myTrackingObj_create(&mytrack_temp);
          myTrackingObj_init_create(mytrack_temp);
          myTrackingObj_addQueue(mytrack_temp,myrect_temp);
          mytrackingObj_updatePointCenter(mytrack_temp,myrect_temp);
          myTrackingObj_updateDistance(mytrack_temp);
          myTrackingObj_updateSpeed(mytrack_temp);
          //mylist = g_list_first(mylist);//reseteando pos
          //mylist = g_list_append(mylist, mytrack_temp);
          mylist = g_list_prepend(mylist, mytrack_temp);
          //mylist = g_list_first(mylist);//reseteando pos
        }

        //myTrackingObj_print(mylist);
      }//fin - if( mylist==NULL)


    printf("    88888888888888888888888888888888888888888888888 for secundario fin %d \n",i);
    }
    
    //myTrackingObj_updateAllFlags(mylist);
    //myTrackingObj_deleletALLBoundingBoxLost(&mylist);
    //myTrackingObj_printListObjInFile(mylist,fp);    
       
    printf("88888888888888888888888888888888888888888888888 for principal fin %d \n",j);
  }


  fclose(fp);

  printf("&&&&&&&&&&&&&&&&&&&xxx11&&&&&&&&&&&&&&&&&&&&&\n");
  myTrackingObj_print(mylist);
  printf("&&&&&&&&&&&&&&&&&&&xxx12&&&&&&&&&&&&&&&&&&&&&\n");

  return 0;
}



///gcc *.c `pkg-config --cflags glib-2.0 pkg-config --libs glib-2.0` -lm