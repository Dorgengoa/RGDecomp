#include "types.h"

extern s32 GetCharaDataMgr_1fdb70(void);
extern s32 CharaDataFindById_1ed990(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    u8 m06;
    u8 m07;
    s32 m08;
    u8 pad00C[0x58];
    s16 m64;
};

s32 CharaResRecSetup_1f4800(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r0;
    s32 r1;

    r0 = GetCharaDataMgr_1fdb70();
    r1 = CharaDataFindById_1ed990(r0, p4);
    if (r1 == 0) {
        return 0;
    }
    p0->m07 = p1;
    p0->m00 = p2;
    p0->m02 = p3;
    p0->m04 = p4;
    p0->m06 = 0;
    p0->m64 = 1;
    p0->m08 = 0;
    return 1;
}
