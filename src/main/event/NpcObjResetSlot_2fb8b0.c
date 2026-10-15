#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002fb8b0 {
    s16 m00;         /* +0x0 */
    u8 pad002[0xC2];
    s16 mC4;         /* +0xC4 */
    u8 pad0C6[0x2];
    s16 mC8;         /* +0xC8 */
    s16 mCA;         /* +0xCA */
} Obj_FUN_002fb8b0;

void NpcObjResetSlot_2fb8b0(Obj_FUN_002fb8b0 *o)
{
    o->mCA = 0;
    o->m00 = 0;
    o->mC8 = -1;
    o->mC4 = -1;
}
