#include "types.h"

extern void * GetDrawCtx_15de80(void);
extern void NameTableFreeGroup_158ac0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
};

struct Obj1 {
    u8 pad000[0x3BA0];
    s32 m3BA0;
};

void EffTexResUnbind_1a8540(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *r0;
    s32 t1;
    s32 t2;

    t0 = p0->m08;
    if (t0 != 0) {
        r0 = GetDrawCtx_15de80();
        t1 = r0->m3BA0;
        t2 = p0->m04;
        NameTableFreeGroup_158ac0(t1, t2);
    }
}
