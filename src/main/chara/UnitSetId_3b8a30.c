#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003b8a30 {
    u8 pad000[0xC];
    s32 m0C;         /* +0xC */
} Obj_FUN_003b8a30;

s32 UnitSetId_3b8a30(Obj_FUN_003b8a30 *o, s32 p1)
{
    o->m0C = p1;
    return 1;
}
