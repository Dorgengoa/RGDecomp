#include "types.h"

extern s32 IsPcCharaId_1f52d0(s32);
extern s32 GetCharaDataMgr_1fdb70(void);
extern s32 PcDefGetCharaDataId_1f5060(s32);
extern s32 CharaDataEnsureLoaded_1f0d00(s32, s32);
extern s32 CharaDataFindById_1ed990(s32, s32);
extern s32 CharaPcBtChrRequestLoadMaybe_1f0af0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaDataEnsureAndLoadBtChrMaybe_1f0c00(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = IsPcCharaId_1f52d0(p1);
    if (r0 == 0) {
        return 0;
    }
    r1 = GetCharaDataMgr_1fdb70();
    r2 = PcDefGetCharaDataId_1f5060(p1);
    r3 = CharaDataEnsureLoaded_1f0d00(p0, p1);
    r4 = CharaDataFindById_1ed990(r1, (r2 + -0x3DD));
    if (r4 != 0) {
        return CharaPcBtChrRequestLoadMaybe_1f0af0(p0, p1);
    }
    return 0;
}
