#include "types.h"

extern void Clear128Bytes_3d2720(void *);

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

s32 InsectRecClearMsgEntries_3cefb0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 l0;
    struct Obj1 * t1;

    t0 = p0->m18;
    if (t0 == 0) {
        return 0;
    }
    p0->m18->m22 = 0;
    l0 = 0;
    do {
        t1 = p0->m18;
        Clear128Bytes_3d2720((struct Obj1 *)((u8 *)(struct Obj1 *)((u8 *)t1 + (l0 << 7)) + 0x4C));
        l0 = (l0 + 1);
    } while (l0 < 0x10);
    return 1;
}
