#include "types.h"

/* Sibling of src/s17q03/EffDefDestroy_1a0a90.c (same HandleTableGet_1a1d50(o+0xB0) handle
   lookup).  `k` is stored to its stack home at entry (mwcc parameter
   homing) but never read again -- see the `volatile` PARAMETER lever
   documented in that sibling file. */
extern s32 *HandleTableGet_1a1d50(void *);
extern void EffDefGetDuration_19aa00(s32);

void EffDefGetDurationByHandle_1a0a50(void *o, s32 k)
{
    volatile s32 sp1C;
    s32 *r;
    s32 v;
    sp1C = k;
    r = HandleTableGet_1a1d50((u8 *)o + 0xB0);
    v = r ? *r : 0;
    EffDefGetDuration_19aa00(v);
}
