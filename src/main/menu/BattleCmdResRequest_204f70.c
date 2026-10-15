#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 NameTableFreeGroup_158ac0(s32, s32);
extern s32 LoaderRequestFile_1cd870(s32, s32, s32);
extern s32 LoaderQueueAppendSeparator_1cd670(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00480274;
extern s32 D_00481C20;
extern u8 D_00481C24;

u8 BattleCmdResRequest_204f70(void)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 t0;
    s32 r3;
    s32 r4;
    s32 t1;

    r0 = GetLoaderMgr_1f59d0();
    r1 = GetDrawCtxNameTable_15de40();
    r2 = NameTableFreeGroup_158ac0(r1, 0x32C);
    t0 = D_00480274;
    D_00481C20 = -1;
    D_00481C24 = 0;
    r3 = LoaderRequestFile_1cd870(r0, t0, 0);
    D_00481C20 = r3;
    r4 = LoaderQueueAppendSeparator_1cd670(r0);
    t1 = D_00481C20;
    return (~t1 == 0);
}
