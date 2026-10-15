#include "types.h"

extern void WaitSema(s32);
extern void SignalSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047E02C;
extern u8 D_0049B100[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 m00;
};

struct Obj1 {
    u8 m00;
    u8 m01;
    u8 m02;
    u8 m03;
    u8 pad004[0x68];
    s32 m6C;
    s32 m70;
    u8 pad074[0x4];
    u8 m78;
};

s32 FileSlotAlloc_1814d0(void)
{
    s32 t0;
    struct Obj0 *l1;
    s32 l2;
    u8 t1;
    s32 rv3;
    struct Obj1 *rv4;
    s32 rv5;
    s32 rv6;
    s32 t2;
    s32 t3;

    t0 = D_0047E02C;
    if (t0 >= 0) {
        WaitSema(t0);
    }
    l1 = (struct Obj0 *)D_0049B100;
    l2 = 0;
    while (l2 < 0xC) {
        t1 = l1->m00;
        if (t1 == 0) {
            break;
        }
        l2 = (l2 + 1);
        l1 = (struct Obj0 *)((u8 *)l1 + 0x7C);
    }
    rv3 = l2;
    rv4 = (struct Obj1 *)l1;
    if (l2 == 0xC) {
        rv4 = 0;
        rv3 = -1;
    }
    rv5 = 0xC;
    if (rv4 != 0) {
        rv4->m03 = 0;
        rv4->m02 = 0;
        rv4->m01 = 0;
        rv4->m00 = 0;
        rv4->m6C = 0;
        rv4->m70 = 1;
        rv4->m78 = 0;
        rv4->m00 = 1;
        t2 = D_0047E02C;
        rv5 = 1;
        rv6 = t2;
    } else {
        t3 = D_0047E02C;
        rv5 = 0xC;
        rv6 = t3;
    }
    if (rv6 >= 0) {
        SignalSema(rv6);
        return rv3;
    }
    return rv3;
}
