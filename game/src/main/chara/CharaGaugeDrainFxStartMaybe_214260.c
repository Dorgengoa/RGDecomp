/* rgp:protos */
#define RGP_SELF_CharaGaugeDrainFxStartMaybe_214260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00214260 {
    u8 pad000[0xB54];
    s32 mB54;         /* +0xB54 */
} Obj_FUN_00214260;

void CharaGaugeDrainFxStartMaybe_214260(Obj_FUN_00214260 *o)
{
    o->mB54 = 0x41F00000;
}
