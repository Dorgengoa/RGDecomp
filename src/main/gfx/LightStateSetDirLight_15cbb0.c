#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

extern struct Obj0 * D_004810A4;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x36B4];
    s32 m36B4;
};

struct Obj1 {
    u128 m00;
};

struct Obj2 {
    u128 m00;
};

void LightStateSetDirLight_15cbb0(s32 p0, struct Obj1 *p1, struct Obj2 *p2)
{
    struct Obj0 * t0;
    s32 t1;
    u128 t2;
    u128 t3;

    t0 = D_004810A4;
    t1 = D_004810A4->m36B4;
    if (t1 != 0) {
        if (p0 >= 0) {
            if (p0 < 4) {
                t2 = p1->m00;
                *(u128 *)((u8 *)t1 + (p0 << 4) + 0x20) = t2;
                *(s32 *)((u8 *)t1 + (p0 << 4) + 0x2C) = 0;
                t3 = p2->m00;
                *(u128 *)((u8 *)t1 + (p0 << 4) + 0x60) = t3;
            }
        }
    }
}
