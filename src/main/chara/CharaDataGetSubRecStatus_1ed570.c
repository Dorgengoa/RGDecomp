#include "types.h"

extern void * CharaDataFindSubRecById_1ed710(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA];
    u8 m0A;
};

u8 CharaDataGetSubRecStatus_1ed570(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *r0;
    u8 t0;

    r0 = CharaDataFindSubRecById_1ed710(p0, p1, p2);
    if (r0 == 0) {
        return (u8)0;
    }
    t0 = r0->m0A;
    return t0;
}
