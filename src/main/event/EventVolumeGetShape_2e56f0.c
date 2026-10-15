#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002e56f0 {
    s32 m00;         /* +0x0 */
} Obj_FUN_002e56f0;

s32 EventVolumeGetShape_2e56f0(Obj_FUN_002e56f0 *o)
{
    return (o->m00 & 0xF);
}
