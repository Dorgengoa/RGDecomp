#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00256d00 {
    u8 pad000[0x940];
    s32 m940;         /* +0x940 */
} Obj_FUN_00256d00;

s32 SplinePathPairIsDone_256d00(Obj_FUN_00256d00 *o)
{
    return (((o->m940 != 0) ^ 1) & 0xFF);
}
