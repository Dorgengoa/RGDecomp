#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d11d0 {
    u8 pad000[0xB494];
    f32 mB494;         /* +0xB494 */
} Obj_FUN_001d11d0;

void GameSceneSoundSetVolumeScale_1d11d0(Obj_FUN_001d11d0 *o, f32 fa0)
{
    o->mB494 = fa0;
}
