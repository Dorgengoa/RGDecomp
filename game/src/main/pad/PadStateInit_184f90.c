/* rgp:protos */
#define RGP_SELF_PadStateInit_184f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    u8 pad01C[0x98];
    s32 mB4;
    s32 mB8;
    s32 mBC;
    s32 mC0;
    s32 mC4;
    u8 pad0C8[0x180];
    s32 m248;
    s32 m24C;
    u8 pad250[0x4];
    s32 m254;
    s32 m258;
    s32 m25C;
    s32 m260;
};

void PadStateInit_184f90(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;
    s32 l2;

    p0->m24C = 0;
    p0->m254 = 1;
    p0->m258 = 0;
    p0->m25C = 0;
    p0->m260 = 0;
    p0->mB4 = -1;
    p0->mB8 = -1;
    p0->mBC = -1;
    p0->m18 = 0;
    p0->m04 = 0;
    p0->m10 = 0x80;
    p0->m14 = 0x80;
    p0->m08 = 0x80;
    p0->m0C = 0x80;
    l0 = 0;
    do {
        *(u8 *)((u8 *)p0 + l0 + 0x2C) = 0;
        *(s32 *)((u8 *)p0 + (l0 << 2) + 0x44) = 0;
        *(u8 *)((u8 *)p0 + l0 + 0x38) = 0xFF;
        l0 = (l0 + 1);
    } while (l0 < 6);
    p0->m248 = 0;
    p0->mC0 = 0;
    p0->mC4 = 0;
    l2 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0xC8) = 0;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x1C8) = 0;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x148) = 0;
        l1 = ((l2 + 1) < 0x20);
        l2 = (l2 + 1);
    } while (l1 != 0);
}
