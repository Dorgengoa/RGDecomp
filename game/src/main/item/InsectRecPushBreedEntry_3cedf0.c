/* rgp:protos */
#define RGP_SELF_InsectRecPushBreedEntry_3cedf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memcpy(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x20];
    s16 m20;
};

s32 InsectRecPushBreedEntry_3cedf0(struct Obj0 *p0, s32 p1)
{
    struct Obj1 * t0;
    s32 rv2;
    s16 t1;
    s32 rv1;
    struct Obj1 * t2;
    s16 t3;

    t0 = p0->m18;
    if (t0 == 0) {
        return 0;
    }
    if (p1 == 0) {
        rv2 = 0;
    } else {
        t1 = p0->m18->m20;
        rv1 = 1;
        if (t1 >= 2) {
            rv1 = 0;
        } else {
            memcpy((struct Obj1 *)((u8 *)(struct Obj1 *)((u8 *)p0->m18 + (t1 * 0x14)) + 0x24), p1, 0x14);
            t2 = p0->m18;
            t3 = p0->m18->m20;
            p0->m18->m20 = (t3 + 1);
            rv1 = 1;
        }
        rv2 = rv1;
    }
    return rv2;
}
