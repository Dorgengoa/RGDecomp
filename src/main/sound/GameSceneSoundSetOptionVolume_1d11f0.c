#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d11f0 {
    u8 pad000[0xB490];
    f32 mB490;         /* +0xB490 */
} Obj_FUN_001d11f0;

void GameSceneSoundSetOptionVolume_1d11f0(Obj_FUN_001d11f0 *o, f32 fa0)
{
    o->mB490 = fa0;
}
