#include "types.h"
/* insect 0x00515170 -- 44 bytes, 11 instructions.
 * 0x43340000 is 180.0f, and it is fs of the second add.s, so the literal is
 * written on the LEFT.
 */

typedef struct Obj {
    u8  pad00[0x71];
    s8  f71;                        /* +0x71 */
    u8  pad72[0xC0 - 0x72];
    f32 fC0;                        /* +0xC0 */
    u8  padC4[0xCC - 0xC4];
    f32 fCC;                        /* +0xCC */
} Obj;

f32 insect_InsectPieceGetYawDeg_515170(Obj *o)
{
    f32 r;

    f32 s;

    s = o->fC0 + o->fCC;
    r = s;
    if (o->f71 == 0) {
        r = 180.0f + s;
    }
    return r;
}
