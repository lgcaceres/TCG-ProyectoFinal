
//#ifndef MYCOMMON_H
//#define MYCOMMON_H

#ifndef __CUDACC__
//#ifndef GPU
//#define __CUDACC__

#include "mytracking_obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "mylist.h"
#include "myrect.h"
//#include "myqueue.h"

#include <gmodule.h>



#define SIZEOF_BUFF 4096
#define LIMIT_QUEUE 40
#define LIMIT_PERDIDA 15	

#define VACIOSTRING "qwerty"
#define DIROUTFILE "./"

#define THRESHOLD_VELOCITY  1.9
#define DESV_DESVIACION_VELOCITY  0.703

#define THRESHOLD_IOU  0.6

//#endif //end MYCOMMON_H

#endif //end MYCOMMON_H

