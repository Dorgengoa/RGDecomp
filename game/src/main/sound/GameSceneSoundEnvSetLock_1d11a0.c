/* rgp:protos */
#define RGP_SELF_GameSceneSoundEnvSetLock_1d11a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d11a0 {
    u8 pad000[0xB48C];
    u8 mB48C;         /* +0xB48C */
} Obj_FUN_001d11a0;

void GameSceneSoundEnvSetLock_1d11a0(Obj_FUN_001d11a0 *o, s32 p1)
{
    o->mB48C = p1;
}
