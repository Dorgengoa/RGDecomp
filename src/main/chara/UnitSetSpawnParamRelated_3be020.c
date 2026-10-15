#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003be020 {
    u8 pad000[0x40A];
    s16 m40A;         /* +0x40A */
} Obj_FUN_003be020;

s32 UnitSetSpawnParamRelated_3be020(Obj_FUN_003be020 *o, s32 p1)
{
    o->m40A = p1;
    return 1;
}
