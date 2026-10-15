#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d1160 {
    u8 pad000[0xB468];
    s16 mB468;         /* +0xB468 */
} Obj_FUN_001d1160;

s32 GameSceneSoundEnvGetCurPresetId_1d1160(Obj_FUN_001d1160 *o)
{
    return o->mB468;
}
