#include "types.h"

extern void GetCharaResMgr_1fdb60(void);
extern void GetEffectMgr_2d9040(void);
extern void CharaEffectGroupsSetPausedHidden_27a300(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaEffectGroupsSetPausedHiddenAll_27a260(s32 p0, s32 p1, s32 p2)
{
    s32 l2;
    s32 l4;

    GetCharaResMgr_1fdb60();
    GetEffectMgr_2d9040();
    l2 = 0;
    do {
        CharaEffectGroupsSetPausedHidden_27a300(l2, p0, p1, p2);
        l2 = (l2 + 1);
    } while (l2 <= 0xB);
    l4 = 0x80;
    do {
        CharaEffectGroupsSetPausedHidden_27a300(l4, p0, p1, -1);
        l4 = (l4 + 1);
    } while (l4 <= 0x9B);
}
