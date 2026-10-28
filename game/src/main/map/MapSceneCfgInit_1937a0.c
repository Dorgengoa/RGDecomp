/* rgp:protos */
#define RGP_SELF_MapSceneCfgInit_1937a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x188];
    s32 m188;
    u8 pad18C[0x10];
    s32 m19C;
    u8 pad1A0[0x14];
    s32 m1B4;
    s32 m1B8;
    s32 m1BC;
    s32 m1C0;
    s32 m1C4;
    s32 m1C8;
};

void MapSceneCfgInit_1937a0(struct Obj0 *p0)
{
    s32 l1;
    s32 l2;

    memset(p0, 0, 0x210);
    p0->m188 = 4;
    p0->m19C = 1;
    p0->m1B4 = 1;
    p0->m1B8 = 1;
    p0->m1BC = 0;
    p0->m1C0 = 1;
    p0->m1C4 = 0;
    p0->m1C8 = 1;
    l1 = 1;
    l2 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x1CC) = 0;
        l1 = ((l2 + 1) < 2);
        l2 = (l2 + 1);
    } while (l1 != 0);
}
