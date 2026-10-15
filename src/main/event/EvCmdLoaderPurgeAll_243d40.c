#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderPurgeAll_1cd240(s32);
extern s32 GetFileNameSlotTable_1ed0c0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdLoaderPurgeAll_243d40(void)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 l3;
    s32 l4;

    r0 = GetLoaderMgr_1f59d0();
    r1 = LoaderPurgeAll_1cd240(r0);
    r2 = GetFileNameSlotTable_1ed0c0();
    l4 = 0;
    do {
        *(u8 *)((u8 *)r2 + (l4 << 8)) = 0;
        *(s32 *)((u8 *)r2 + (l4 << 2) + 0x1000) = -1;
        l3 = ((l4 + 1) < 0x10);
        l4 = (l4 + 1);
    } while (l3 != 0);
    return 1;
}
