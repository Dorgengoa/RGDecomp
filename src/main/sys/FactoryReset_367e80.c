#include "types.h"

extern s32 MemStackClear_14dff0(void *);
extern void FactorySetObj_367f20(s32);
extern void FactorySetMapHeap_367ef0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004830EC;
extern s32 D_004830F4;
extern u8 D_004E9020[];

void FactoryReset_367e80(void)
{
    s32 r0;

    r0 = MemStackClear_14dff0(D_004E9020);
    D_004830EC = -1;
    FactorySetObj_367f20(0);
    FactorySetMapHeap_367ef0(0);
    D_004830F4 = -1;
}
