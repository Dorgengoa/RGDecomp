#include "types.h"

/* D_004E72B0 is reached by %hi/%lo => incomplete array.  The two halfword
   stores are the first two s16 members of that object. */

extern s16 D_004E72B0[];

extern void NpcObjTableInit_2fb710(void *p);
extern void NpcObjTableAlloc_2fb740(void *p, void *q, s32 n);

void NpcObjTableSetup_312800(void *arg)
{
    NpcObjTableInit_2fb710(D_004E72B0);
    NpcObjTableAlloc_2fb740(D_004E72B0, arg, 0x1E);
    D_004E72B0[0] = 0xC0;
    D_004E72B0[1] = 0x20;
}
