#include "types.h"

extern s32 GetCharaDataMgr_1fdb70(void);
extern void * CharaDataFindById_1ed990(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x6C];
    s16 m6C;
};

s16 CharaDataGetRefCount_1f0480(s32 p0, s32 p1)
{
    s32 r0;
    struct Obj0 *r1;
    s16 t0;

    r0 = GetCharaDataMgr_1fdb70();
    r1 = CharaDataFindById_1ed990(r0, p1);
    if (r1 == 0) {
        return (s16)0;
    }
    t0 = r1->m6C;
    return t0;
}
