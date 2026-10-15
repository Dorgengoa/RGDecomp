#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0014a530 {
    u8 pad000[0x14];
    s32 m14;         /* +0x14 */
    u8 pad018[0x11];
    u8 m29;         /* +0x29 */
    u8 pad02A[0x1];
    u8 m2B;         /* +0x2B */
} Obj_FUN_0014a530;

void ModelFrameSetPosLink_14a530(Obj_FUN_0014a530 *o, s32 p1)
{
    o->m14 = p1;
    o->m2B = 1;
    o->m29 = 1;
}
