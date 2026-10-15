#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d0460 {
    u8 pad000[0xB4B8];
    f32 mB4B8;         /* +0xB4B8 */
} Obj_FUN_001d0460;

void GameSceneAmbientSetVolume_1d0460(Obj_FUN_001d0460 *o, f32 fa0)
{
    o->mB4B8 = fa0;
}
