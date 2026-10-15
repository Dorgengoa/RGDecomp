#include "types.h"
/* normal 0x00518A50 -- guarded pair of teardown calls on one gp handle. */

extern void *D_00484724;   /* gp - 0xA4C */

extern void func_375B10(void *w, s32 a);
extern void func_375D10(void *w);

void normal_TransSaveIconSysInit_518a50(s32 a)
{
    if (a != 0) {
        func_375B10(D_00484724, a);
        func_375D10(D_00484724);
    }
}
