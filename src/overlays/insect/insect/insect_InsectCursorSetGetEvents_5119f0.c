#include "types.h"
/* insect 0x005119F0 -- 72 bytes, 18 instructions.  The member at +0x30 is a
 * 64-bit word (`ld`), so the s32 mask is sign-extended into it and the s32
 * return is sign-extended back out (`dsll32`/`dsra32 ..,0`).  0xFFFFFFFF is
 * built by `ori`/`dsll 16`/`ori` because it is a 64-bit-wide constant.
 *
 * The `bnel $5, $2` carries the TARGET block's `ld $2, 0x30($4)`, so the
 * m != -1 arm is the `else` and the -1 arm is the fall-through `if` body. */

typedef struct Obj {
    u8  pad00[0x30];
    s64 f30;                        /* +0x30 */
} Obj;

s32 insect_InsectCursorSetGetEvents_5119f0(Obj *o, s32 m)
{
    if (m == -1) {
        return o->f30 & 0xFFFFFFFF;
    }
    return o->f30 & m;
}
