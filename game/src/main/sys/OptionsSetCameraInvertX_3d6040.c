/* rgp:protos */
#define RGP_SELF_OptionsSetCameraInvertX_3d6040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003d6040 {
    u8 pad000[0x1A];
    s16 m1A;         /* +0x1A */
} Obj_FUN_003d6040;

void OptionsSetCameraInvertX_3d6040(Obj_FUN_003d6040 *o, s32 p1)
{
    o->m1A = ((o->m1A & -5) | (p1 & 4));
}
