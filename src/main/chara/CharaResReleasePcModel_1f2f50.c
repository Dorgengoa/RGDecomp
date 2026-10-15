#include "types.h"

extern s32 GetCharaDataMgr_1fdb70(void);
extern s32 CharaDataFindSubRecById_1ed710(s32, s32, s32);
extern s32 CharaDataSubRecRelease_1ee6d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
};

s32 CharaResReleasePcModel_1f2f50(struct Obj0 *p0)
{
    s32 r0;
    s16 t0;
    s32 r1;
    s32 r2;

    r0 = GetCharaDataMgr_1fdb70();
    t0 = p0->m04;
    r1 = CharaDataFindSubRecById_1ed710(r0, t0, 1);
    r2 = CharaDataSubRecRelease_1ee6d0(r1);
    return r2;
}
