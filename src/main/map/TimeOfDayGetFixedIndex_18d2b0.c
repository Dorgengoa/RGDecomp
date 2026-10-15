#include "types.h"

/* ONE symbol, TWO entries: a `j` TAIL CALL into the second entry with the
   `this` adjusted by +0x70, then a plain member read. */

typedef struct A18D2B0 {
    u8  pad000[0x98];
    s32 m98;
} A18D2B0;

s32 FUN_0018d2b0_e1(A18D2B0 *p);

s32 TimeOfDayGetFixedIndex_18d2b0(u8 *p)
{
    return FUN_0018d2b0_e1((A18D2B0 *)(p + 0x70));
}

s32 FUN_0018d2b0_e1(A18D2B0 *p)
{
    return p->m98;
}
