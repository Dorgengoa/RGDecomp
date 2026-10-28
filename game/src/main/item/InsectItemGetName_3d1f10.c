/* rgp:protos */
#define RGP_SELF_InsectItemGetName_3d1f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void strncpy(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

struct Obj1 {
    u8 pad000[0x10];
    u8 m10;
};

s32 InsectItemGetName_3d1f10(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    s32 t1;

    if (p1 != 0) {
        t0 = p0->m18;
        strncpy(p1, (t0 + 1), 0x10);
        p1->m10 = 0;
    }
    t1 = p0->m18;
    return (t1 + 1);
}
