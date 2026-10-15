#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x28];
    s32 m28;
};

struct Obj1 {
    s16 m00;
    s16 m02;
    s32 m04;
};

void UiTextColumnLayoutMaybe_393700(s32 p0, struct Obj0 *p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    s32 t0;
    struct Obj1 *l1;
    s32 l0;
    s32 t1;

    if (p1 != 0) {
        t0 = p1->m28;
        if (t0 != 0) {
            l1 = (struct Obj1 *)t0;
            l0 = 0;
            while (l0 < p6) {
                l1->m00 = p3;
                l1->m02 = (p4 + (p5 * l0));
                if (p2 != 0) {
                    t1 = *(s32 *)((u8 *)p2 + (l0 << 2));
                    l1->m04 = t1;
                }
                l1 = (struct Obj1 *)((u8 *)l1 + 0x10);
                l0 = (l0 + 1);
            }
            return;
        }
        return;
    }
}
