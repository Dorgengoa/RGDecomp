#include "types.h"

extern void CharaMoveReqResetThunk_2194d0(void);
extern void VecCopy_1cbe30(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    u8 pad014[0x4];
    s32 m18;
};

void CharaMoveReqSet_219310(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 rv1;

    CharaMoveReqResetThunk_2194d0();
    rv1 = p2;
    if (p2 <= 0) {
        rv1 = 1;
    }
    VecCopy_1cbe30(p0, p1);
    p0->m10 = rv1;
    p0->m18 = p3;
}
