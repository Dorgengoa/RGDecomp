/* rgp:protos */
#define RGP_SELF_EffParticleGetMatrix_199f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00199f00 {
    u8 pad000[0xB0];
    s32 mB0;         /* +0xB0 */
    s32 mB4;         /* +0xB4 */
} Obj_FUN_00199f00;

s32 EffParticleGetMatrix_199f00(Obj_FUN_00199f00 *o)
{
    return (o->mB4 + (o->mB0 << 4));
}
