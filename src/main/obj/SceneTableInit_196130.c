#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x20C];
    s32 m210;
};

void SceneTableInit_196130(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    p0->m00 = 0x20;
    l0 = 0;
    while (l0 < p0->m00) {
        *(s32 *)((u8 *)p0 + (l0 << 4) + 0x10) = 0;
        *(s32 *)((u8 *)p0 + (l0 << 4) + 0x14) = 0;
        *(s32 *)((u8 *)p0 + (l0 << 4) + 0x18) = 0;
        l0 = (l0 + 1);
    }
    p0->m210 = 0x20;
    l1 = 0;
    while (l1 < p0->m210) {
        *(s32 *)((u8 *)p0 + (l1 << 3) + 0x214) = 0;
        *(s32 *)((u8 *)p0 + (l1 << 3) + 0x218) = 0;
        l1 = (l1 + 1);
    }
}
