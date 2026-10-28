/* rgp:protos */
#define RGP_SELF_OptionsSetCameraBitMaybe_3d6080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003d6080 {
    u8 pad000[0x1A];
    s16 m1A;         /* +0x1A */
} Obj_FUN_003d6080;

void OptionsSetCameraBitMaybe_3d6080(Obj_FUN_003d6080 *o, s32 p1)
{
    o->m1A = ((o->m1A & -2) | (p1 & 1));
}
