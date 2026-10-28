/* rgp:protos */
#define RGP_SELF_GameSceneGetBgmTrack_1d1170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d1170 {
    u8 pad000[0xB46A];
    s16 mB46A;         /* +0xB46A */
} Obj_FUN_001d1170;

s32 GameSceneGetBgmTrack_1d1170(Obj_FUN_001d1170 *o)
{
    return o->mB46A;
}
