/* rgp:protos */
#define RGP_SELF_MovingLinePushPoint_2d6330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x120];
    s16 m120;
    s16 m122;
    f32 m124;
    s32 m128;
    s32 m12C;
};

struct Obj1 {
    u8 pad000[0xC];
    s32 m0C;
};

void MovingLinePushPoint_2d6330(struct Obj0 *p0, struct Obj1 *p1, f32 fa0)
{
    s16 t0;
    s32 t1;
    s32 t2;
    s32 l0;
    s32 t3;
    s32 t4;

    t0 = p0->m120;
    if (t0 != 0) {
        p1->m0C = 0x3F800000;
        t1 = p0->m12C;
        t2 = p0->m128;
        if (t1 == t2) {
            l0 = 1;
            while (l0 < p0->m128) {
                sceVu0CopyVector((struct Obj0 *)((u8 *)p0 + ((l0 + -1) << 4)), (struct Obj0 *)((u8 *)p0 + (l0 << 4)));
                l0 = (l0 + 1);
            }
            t3 = p0->m12C;
            sceVu0CopyVector((struct Obj0 *)((u8 *)p0 + ((t3 + -1) << 4)), p1);
        } else {
            sceVu0CopyVector((struct Obj0 *)((u8 *)p0 + (t1 << 4)), p1);
            t4 = p0->m12C;
            p0->m12C = (t4 + 1);
        }
        p0->m122 = 1;
        p0->m124 = fa0;
        return;
    }
}
