/* rgp:protos */
#define RGP_SELF_CharaGaugeFullFxStartMaybe_214250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00214250 {
    u8 pad000[0xB58];
    s32 mB58;         /* +0xB58 */
} Obj_FUN_00214250;

void CharaGaugeFullFxStartMaybe_214250(Obj_FUN_00214250 *o)
{
    o->mB58 = 0x41F00000;
}
