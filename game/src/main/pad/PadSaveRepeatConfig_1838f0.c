/* rgp:protos */
#define RGP_SELF_PadSaveRepeatConfig_1838f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xC0];
    s32 mC0;
    u8 pad0C4[0x184];
    s32 m248;
};

struct Obj1 {
    s32 m00;
    u8 pad004[0x100];
    u8 m104;
    u8 m105;
};

void PadSaveRepeatConfig_1838f0(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    s32 l0;
    s32 l1;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;

    t0 = p0->mC0;
    p1->m00 = t0;
    l0 = t0;
    l1 = 0;
    do {
        t1 = *(s32 *)((u8 *)p0 + (l1 << 2) + 0x148);
        *(s32 *)((u8 *)p1 + (l1 << 2) + 0x4) = t1;
        t2 = *(s32 *)((u8 *)p0 + (l1 << 2) + 0x1C8);
        *(s32 *)((u8 *)p1 + (l1 << 2) + 0x84) = t2;
        l0 = ((l1 + 1) < 0x20);
        l1 = (l1 + 1);
    } while (l0 != 0);
    t3 = p0->m248;
    p1->m104 = (t3 > 0);
    t4 = p0->m248;
    p1->m105 = (t4 != 0);
}
