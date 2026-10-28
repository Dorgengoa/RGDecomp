/* rgp:protos */
#define RGP_SELF_CharaSetAppearMode_213fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00213fb0 {
    u8 pad000[0xB48];
    s16 mB48;         /* +0xB48 */
    s16 mB4A;         /* +0xB4A */
} Obj_FUN_00213fb0;

void CharaSetAppearMode_213fb0(Obj_FUN_00213fb0 *o, s16 p0, s16 p1)
{
    o->mB48 = p0;
    o->mB4A = p1;
}
