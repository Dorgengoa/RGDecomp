#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d1190 {
    u8 pad000[0xB48D];
    u8 mB48D;         /* +0xB48D */
} Obj_FUN_001d1190;

s32 GameSceneSoundPollIsHeld_1d1190(Obj_FUN_001d1190 *o)
{
    return o->mB48D;
}
