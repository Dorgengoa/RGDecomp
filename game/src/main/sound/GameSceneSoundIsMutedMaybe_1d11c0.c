/* rgp:protos */
#define RGP_SELF_GameSceneSoundIsMutedMaybe_1d11c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d11c0 {
    u8 pad000[0xB498];
    u8 mB498;         /* +0xB498 */
} Obj_FUN_001d11c0;

s32 GameSceneSoundIsMutedMaybe_1d11c0(Obj_FUN_001d11c0 *o)
{
    return o->mB498;
}
