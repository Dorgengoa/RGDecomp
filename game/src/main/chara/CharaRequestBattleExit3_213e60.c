/* rgp:protos */
#define RGP_SELF_CharaRequestBattleExit3_213e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00213e60 {
    u8 pad000[0xB4C];
    s16 mB4C;         /* +0xB4C */
    s16 mB4E;         /* +0xB4E */
    s16 mB50;         /* +0xB50 */
    s16 mB52;         /* +0xB52 */
} Obj_FUN_00213e60;

void CharaRequestBattleExit3_213e60(Obj_FUN_00213e60 *o)
{
    o->mB50 = 3;
    o->mB52 = 0;
    o->mB4C = 0;
    o->mB4E = 0;
}
