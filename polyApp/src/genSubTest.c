#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <dbEvent.h>
#include <dbDefs.h>
#include <dbCommon.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>

static long genSubTest(aSubRecord *pgenSub)
{
    double v[1024];
    static double cnt =0.;
    int i;

    for(i=0;i<1024;i++)  {
        v[i] = cnt;
        cnt += 1.;
    }

    memcpy(pgenSub->vala, v, 1024*sizeof(double));

    return(0);
}

epicsRegisterFunction(genSubTest);
