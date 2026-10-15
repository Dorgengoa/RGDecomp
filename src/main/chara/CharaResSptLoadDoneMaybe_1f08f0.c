#include "types.h"

extern s32 GetCharaDataMgr_1fdb70(void);
extern void * CharaResFindById_1efba0(s32, s32);
extern s32 PcDefGetCharaDataId_1f5060(s32);
extern s32 CharaDataGetSubRecStatus_1ed570(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
};

u8 CharaResSptLoadDoneMaybe_1f08f0(s32 p0, s32 p1)
{
    s32 r0;
    struct Obj0 *r1;
    s16 t0;
    s32 r2;
    s32 r3;

    r0 = GetCharaDataMgr_1fdb70();
    r1 = CharaResFindById_1efba0(p0, p1);
    if (r1 == 0) {
        return (u8)1;
    }
    t0 = r1->m02;
    r2 = PcDefGetCharaDataId_1f5060(t0);
    r3 = CharaDataGetSubRecStatus_1ed570(r0, (r2 + -0x3DD), 4);
    return ((u32)(r3 + -3) < 2);
}
