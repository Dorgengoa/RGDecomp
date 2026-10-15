#include "types.h"

extern s32 PollSema(s32);
extern s32 SignalSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047E020;
extern s32 D_00481204;
extern u8 D_00495FD0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
    u8 pad00C[0x114];
    s32 m120;
};

u8 FileReqAnyIncomplete_1825f0(void)
{
    s32 t0;
    s32 r0;
    s32 rv2;
    s32 t1;
    s32 r1;
    s32 l4;
    struct Obj0 *l3;
    s32 t2;
    s32 rv5;
    s32 t3;
    s32 t4;

    t0 = D_0047E020;
    D_00481204 = 0;
    r0 = PollSema(t0);
    rv2 = r0;
    if (r0 < 0) {
        t1 = D_0047E020;
        r1 = SignalSema(t1);
        rv2 = r1;
    }
    l4 = 0;
    l3 = (struct Obj0 *)D_00495FD0;
    while (l4 < 0x20) {
        t2 = l3->m120;
        rv5 = t2;
        if (t2 != 0) {
            t3 = l3->m04;
            if (t3 == 0) {
                break;
            }
            t4 = l3->m08;
            if (t4 == 0) {
                break;
            }
            rv5 = t4;
        }
        l4 = (l4 + 1);
        l3 = (struct Obj0 *)((u8 *)l3 + 0x128);
    }
    return ((l4 ^ 0x20) != 0);
}
