/* rgp:protos */
#define RGP_SELF_GameSceneSoundSetPollHold_1d1180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d1180 {
    u8 pad000[0xB48D];
    u8 mB48D;         /* +0xB48D */
} Obj_FUN_001d1180;

void GameSceneSoundSetPollHold_1d1180(Obj_FUN_001d1180 *o, s32 p1)
{
    o->mB48D = p1;
}
