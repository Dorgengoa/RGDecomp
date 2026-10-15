#include "types.h"

extern void memset(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_00465C88;

struct Obj0;

struct Obj0 {
    u8 pad000[0x23C];
    s32 m23C;
    s32 m240;
};

void CharaSysClearTable23C_3a3630(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 l0;
    s32 t2;

    p0->m240 = 0;
    t0 = p0->m23C;
    if (t0 != 0) {
        t1 = D_00465C88;
        l0 = 0;
        while (l0 < t1) {
            t2 = p0->m23C;
            memset((t2 + (l0 << 4)), 0, 0x10);
            l0 = (l0 + 1);
        }
        return;
    }
}
