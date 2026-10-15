#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00257090 {
    u8 pad000[0x204];
    s32 m204;         /* +0x204 */
} Obj_FUN_00257090;

s32 SplinePathPairSetDuration_257090(Obj_FUN_00257090 *o, s32 p1)
{
    o->m204 = p1;
    return 0;
}
