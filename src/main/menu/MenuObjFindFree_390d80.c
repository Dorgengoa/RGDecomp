#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004832AC;

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 MenuObjFindFree_390d80(struct Obj0 *p0)
{
    s32 l0;

    if (p0 != 0) {
        p0->m00 = -1;
    }
    l0 = 0;
    while (l0 < 5) {
        if (*(s8 *)((u8 *)D_004832AC + (l0 * 0x9D0) + 0x985) == 0) {
            if (p0 != 0) {
                p0->m00 = l0;
            }
            return (D_004832AC + (l0 * 0x9D0));
        }
        l0 = (l0 + 1);
    }
    return 0;
}
