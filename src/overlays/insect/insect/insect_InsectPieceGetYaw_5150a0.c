#include "types.h"
/* insect 0x005150A0 -- 44 bytes, 11 instructions, no calls.  Three f32
 * out-parameters; the FIRST one is unconditional, the other two are guarded. */

typedef struct Obj {
    u8  pad00[0xC0];
    f32 mC0;                        /* +0xC0 */
    f32 mC4;                        /* +0xC4 */
    f32 mC8;                        /* +0xC8 */
} Obj;

void insect_InsectPieceGetYaw_5150a0(Obj *o, f32 *a, f32 *b, f32 *c)
{
    *a = o->mC0;
    if (b != 0) {
        *b = o->mC4;
    }
    if (c != 0) {
        *c = o->mC8;
    }
}
