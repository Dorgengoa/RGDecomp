#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderRequestFile_1cd870(s32, s32, s32);
extern s32 LoaderQueueAppendSeparator_1cd670(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481BB0;
extern s32 D_00481C10;

s32 MenuBattleEndResRequest_2045e0(void)
{
    s32 r0;
    s32 r2;
    s32 l3;
    s32 t0;
    s32 r4;
    s32 r5;

    r0 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r0, 0x32D);
    r2 = GetLoaderMgr_1f59d0();
    l3 = 0;
    while (l3 < 2) {
        *(s32 *)((u8 *)&D_00481C10 + (l3 << 3)) = -1;
        t0 = *(s32 *)((u8 *)&D_00481BB0 + (l3 << 2));
        *(u8 *)((u8 *)&D_00481C10 + (l3 << 3) + 0x4) = 0;
        r4 = LoaderRequestFile_1cd870(r2, t0, 0);
        *(s32 *)((u8 *)&D_00481C10 + (l3 << 3)) = r4;
        if (r4 == -1) {
            return 1;
        }
        l3 = (l3 + 1);
    }
    r5 = LoaderQueueAppendSeparator_1cd670(r2);
    return 0;
}
