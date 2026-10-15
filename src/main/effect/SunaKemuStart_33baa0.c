#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern void * NameTableFindByName_159fb0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    struct Obj1 *m10;
    s32 m14;
    u8 pad018[0xC8];
    s32 mE0;
};

struct Obj1 {
    s16 m00;
};

void SunaKemuStart_33baa0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    struct Obj1 *r1;
    struct Obj1 * rv2;
    s16 t0;

    r0 = GetDrawCtxNameTable_15de40();
    r1 = NameTableFindByName_159fb0(r0, p1, -1);
    p0->m10 = r1;
    rv2 = 0;
    if (r1 != 0) {
        t0 = r1->m00;
        p0->m14 = t0;
        rv2 = r1;
    }
    p0->mE0 = 0x3F800000;
}
