#include "types.h"

extern void PathLocalize_1c28c0(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045B200[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x80];
    u8 m80;
    u8 pad081[0x57];
    s32 mD8;
    s32 mDC;
    u8 mE0;
    u8 mE1;
};

void MovieOpenParamInit_1d6230(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0xC0) = 0;
        l0 = ((l1 + 1) < 6);
        l1 = (l1 + 1);
    } while (l0 != 0);
    p0->mE0 = 1;
    p0->mE1 = 0;
    p0->mD8 = 0x200;
    p0->mDC = 0x1C0;
    PathLocalize_1c28c0(p0, D_0045B200);
    p0->m80 = 0;
}
