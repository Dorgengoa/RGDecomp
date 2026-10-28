/* rgp:protos */
#define RGP_SELF_EventCastRecordInit_24e080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047DA0C;
extern f32 D_0047DD24;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x4];
    s32 m0C;
    s32 m10;
    u8 pad014[0x8];
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
    u8 pad050[0x80];
    s32 mD0;
    s32 mD4;
};

void EventCastRecordInit_24e080(struct Obj0 *p0)
{
    f32 t0;
    f32 t1;
    s32 l1;
    s32 l2;

    p0->m0C = 0;
    p0->m04 = 0;
    p0->m00 = 0;
    p0->m1C = -1;
    p0->m20 = -1;
    p0->m28 = 0;
    p0->m2C = 0;
    p0->m24 = -1;
    p0->m10 = -1;
    p0->m3C = 0;
    p0->m40 = 1;
    p0->m30 = 0;
    p0->m34 = 0;
    p0->m38 = -1;
    p0->m3C = 0;
    p0->m44 = -1;
    p0->m48 = 0x3F800000;
    p0->m4C = 0;
    HeadLookInit_1c5c50((struct Obj0 *)((u8 *)p0 + 0x50));
    t0 = D_0047DA0C;
    t1 = D_0047DD24;
    p0->mD0 = -1;
    l2 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0xE0) = 0;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0xE8) = 0;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0xF8) = 0;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0xD8) = 0;
        *(f32 *)((u8 *)p0 + (l2 << 2) + 0x100) = t0;
        *(f32 *)((u8 *)p0 + (l2 << 3) + 0x108) = t1;
        *(f32 *)((u8 *)p0 + (l2 << 3) + 0x10C) = t1;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x118) = -1;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x120) = -1;
        *(s32 *)((u8 *)p0 + (l2 << 2) + 0x128) = 0;
        l1 = ((l2 + 1) < 2);
        l2 = (l2 + 1);
    } while (l1 != 0);
    p0->mD4 = 0;
}
