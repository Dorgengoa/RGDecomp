#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetCharaResMgr_1fdb60(void);
extern void CharaResDeferReleaseById_1f1120(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaResDeferReleaseByIdGlobal_2f2e80(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = GetCurrentScene_1f5be0();
    r1 = GetCharaResMgr_1fdb60();
    CharaResDeferReleaseById_1f1120(r1, r0, p0);
}
