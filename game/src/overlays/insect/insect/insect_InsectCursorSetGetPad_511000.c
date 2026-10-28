/* rgp:protos */
#define RGP_SELF_insect_InsectCursorSetGetPad_511000 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00511000 -- 136 bytes, 34 instructions, no calls.  A flag-driven
 * selector between two words of the same object.  The `beql` pairs put each
 * following test in the annulled delay slot, and the two `lw 0x0` sites are
 * the one `r = o->f00;` tail-duplicated. */

typedef struct Obj {
    s32 f00;                        /* +0x00 */
    s32 f04;                        /* +0x04 */
    u8  pad08[0x2C - 0x08];
    u8  f2C;                        /* +0x2C */
} Obj;

s32 insect_InsectCursorSetGetPad_511000(Obj *o, s32 a)
{
    u8  fl;
    s32 r;

    fl = o->f2C;
    if (fl & 0x20) {
        return o->f04;
    }
    if (fl & 0x10) {
        return o->f00;
    }
    if (a != -1) {
        if (a == 0) {
            return o->f00;
        }
        if (a == 1) {
            return o->f04;
        }
    }
    r = o->f00;
    if (fl & 1) {
        if (fl & 8) {
            r = o->f04;
        }
    } else {
        if (fl & 4) {
            r = o->f04;
        }
    }
    return r;
}
