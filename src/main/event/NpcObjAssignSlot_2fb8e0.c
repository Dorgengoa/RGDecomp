#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002fb8e0 {
    u8 pad000[0xC4];
    s16 mC4;         /* +0xC4 */
    u8 pad0C6[0x4];
    s16 mCA;         /* +0xCA */
} Obj_FUN_002fb8e0;

s32 NpcObjAssignSlot_2fb8e0(Obj_FUN_002fb8e0 *o, s32 p1)
{
    o->mC4 = p1;
    o->mCA = 2;
    return 1;
}
