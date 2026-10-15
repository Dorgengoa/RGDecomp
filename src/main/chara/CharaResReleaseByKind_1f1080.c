#include "types.h"

extern void CharaResRecRelease_1f4510(void *, s32, s32);
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern void MemStackHeapReinit_14de90(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x7];
    u8 m07;
};

struct Obj1 {
    u8 pad000[0xD00];
    s32 mD00;
};

void CharaResReleaseByKind_1f1080(struct Obj1 *p0, s32 p1, s32 p2)
{
    struct Obj0 *l0;
    s32 l1;
    u8 t0;
    s32 t1;
    s32 t2;

    l0 = (struct Obj0 *)p0;
    l1 = 0;
    do {
        t0 = l0->m07;
        if (p2 == t0) {
            t1 = p0->mD00;
            CharaResRecRelease_1f4510(l0, p1, t1);
        }
        l0 = (struct Obj0 *)((u8 *)l0 + 0x68);
        l1 = (l1 + 1);
    } while (l1 < 0x20);
    DrawCtxVif1HandlerStop_15dc40();
    t2 = p0->mD00;
    if (t2 != 0) {
        MemStackHeapReinit_14de90(t2);
        return;
    }
}
