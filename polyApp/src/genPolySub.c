/* ===================================================================
  
   Filename: genPolySub.c

   Abs:      This file contains generic polynomial subroutine which
             uses genSub record.

   Rem:      The maximum order of polynomial is limited 10th.

=======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <dbEvent.h>
#include <dbDefs.h>
#include <dbCommon.h>
#include <registryFunction.h>
#include <genSubRecord.h>
#include <epicsExport.h>

#define  MAX_INDEX 10
#define  DEBUG_

#ifdef DEBUG
#ifdef _X86_
static unsigned char amIFirst=0;
static unsigned long long int counter_per_sec;

__inline__ unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile(".byte 0x0f, 0x31" : "=A" (x));
    return x;
}
#endif
#endif

static long genPolyInit(genSubRecord *pgenSub)
{
#ifdef DEBUG
#ifdef _X86_
    unsigned  long long int start, end;
    if(!amIFirst) {
      amIFirst = 1;
      start = rdtsc();
      epicsThreadSleep(1.);
      end = rdtsc();
      counter_per_sec = end - start;
      epicsPrintf("genPolySub: Estimated CPU clock is %7.3fGHz..\n",
                  (double)counter_per_sec * 1.E-9);
    }
#endif
#endif
    return(0);
}

/* ==============================================================
    Function:    y(x) := SUM_{i=0_to_9} {C_i * x^i}

    INPA ... INPJ: C_i
    INPT: Lower limit of Input value
    INPU: Upper limit of Input value
    INPS: x the input value
    OUTA, VALA: y Output LINK and Output vlaue
    OUTB, VALB: Vector of C_i, Output LINK and Output vlaue
    ============================================================= */

static long genPolySub(genSubRecord *pgenSub)
{
#ifdef DEBUG
#ifdef _X86_
    unsigned long long int start, end;
#endif
#endif
    int i;
    double x, y;
    double *val     = (double*)pgenSub->vala;
    double *coeff   = (double*)pgenSub->valb;
#ifdef DEBUG
#ifdef _X86_
    double *spinTime = (double*)pgenSub->valc;
#endif
#endif
    double llim     = *(double*)pgenSub->t;
    double ulim     = *(double*)pgenSub->u;

    double val_inp     = *(double*)pgenSub->s;
    double **coeff_inp = (double**) &pgenSub->a;

#ifdef DEBUG
#ifdef _X86_
    start = rdtsc();
#endif
#endif

    x = 1.; y = 0.;

    if(llim != 0. || ulim != 0.) {
        if(val_inp < llim) val_inp = llim;
        if(val_inp > ulim) val_inp = ulim;
    }

    for(i=0;i<MAX_INDEX;i++) {
        coeff[i] = *(coeff_inp[i]);
        y += coeff[i] * x;
        x *= val_inp;
    }

    *val = y;

#ifdef DEBUG
#ifdef _X86_
    end = rdtsc();
    *spinTime = (double)(end-start)*1.E+6/(double)(counter_per_sec);
#endif
#endif

    return(0);

}

epicsRegisterFunction(genPolyInit);
epicsRegisterFunction(genPolySub);
