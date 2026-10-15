#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003d6060 {
    u8 pad000[0x1A];
    s16 m1A;         /* +0x1A */
} Obj_FUN_003d6060;

void OptionsSetCameraInvertY_3d6060(Obj_FUN_003d6060 *o, s32 p1)
{
    o->m1A = ((o->m1A & -3) | (p1 & 2));
}
