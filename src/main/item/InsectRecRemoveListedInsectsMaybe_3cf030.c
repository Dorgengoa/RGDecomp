#include "types.h"

extern s32 InsectRecSlotFindItemById_3cfad0(void *, s32);
extern void InsectRecSlotRemoveItem_3cfde0(void *, s32, s32);

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
    u8 pad000[0x22];
    s16 m22;
};

void InsectRecRemoveListedInsectsMaybe_3cf030(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 l0;
    s16 t1;
    s16 t2;
    s32 r1;

    t0 = p0->m18;
    if (t0 != 0) {
        l0 = 0;
        while (l0 < p0->m18->m22) {
            t1 = *(s16 *)((u8 *)p0->m18 + (l0 << 7) + 0x8C);
            if (t1 == 4) {
                t2 = *(s16 *)((u8 *)p0->m18 + (l0 << 7) + 0x8E);
                r1 = InsectRecSlotFindItemById_3cfad0(p0, t2);
                InsectRecSlotRemoveItem_3cfde0(p0, r1, 1);
            }
            l0 = (l0 + 1);
        }
        return;
    }
}
