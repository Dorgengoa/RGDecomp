#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

void SoundNoteListReset_1b4e80(struct Obj0 *p0)
{
    s32 t0;
    s32 l0;
    s32 t1;

    t0 = p0->m04;
    if (t0 != 0) {
        l0 = 0;
        while (l0 < p0->m00) {
            t1 = p0->m04;
            *(s32 *)((u8 *)t1 + (l0 * 0x14)) = -1;
            *(s32 *)((u8 *)t1 + (l0 * 0x14) + 0xC) = 0xBF800000;
            *(s32 *)((u8 *)t1 + (l0 * 0x14) + 0x10) = 0;
            l0 = (l0 + 1);
        }
        return;
    }
}
