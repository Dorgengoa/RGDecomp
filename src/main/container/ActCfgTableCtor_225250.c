#include "types.h"

/* %hi/%lo on every table => incomplete-array externs.  Each vtable store
   sits in the delay slot of the FOLLOWING call, i.e. it precedes it. */

extern u8 D_00471470[];
extern u8 D_00471460[];
extern u8 D_00471450[];
extern u8 D_00471440[];
extern u8 D_00471430[];
extern u8 D_00471420[];
extern void DListInit_42eae0(void *p);
extern void ActCfgTableReset_225160(void *p);

void *ActCfgTableCtor_225250(void *p)
{
    u8 *q;

    q = (u8 *)p + 0x7C;
    DListInit_42eae0(q);
    *(u8 **)(q + 0xC) = D_00471470;
    DListInit_42eae0(q);
    *(u8 **)(q + 0xC) = D_00471460;
    DListInit_42eae0(q);
    *(u8 **)(q + 0xC) = D_00471450;
    DListInit_42eae0(q);
    q = (u8 *)p + 0x8C;
    DListInit_42eae0(q);
    *(u8 **)(q + 0xC) = D_00471440;
    DListInit_42eae0(q);
    *(u8 **)(q + 0xC) = D_00471430;
    DListInit_42eae0(q);
    *(u8 **)(q + 0xC) = D_00471420;
    DListInit_42eae0(q);
    ActCfgTableReset_225160(p);
    return p;
}
