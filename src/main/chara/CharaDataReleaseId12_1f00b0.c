#include "types.h"

extern s32 GetCharaDataMgr_1fdb70(void);
extern void CharaDataReleaseById_1ed850(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaDataReleaseId12_1f00b0(void)
{
    s32 r0;

    r0 = GetCharaDataMgr_1fdb70();
    CharaDataReleaseById_1ed850(r0, 0xC);
}
