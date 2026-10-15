#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00213fa0 {
    u8 pad000[0xB4C];
    s16 mB4C;         /* +0xB4C */
    s16 mB4E;         /* +0xB4E */
} Obj_FUN_00213fa0;

void CharaSetBattleEnterReq_213fa0(Obj_FUN_00213fa0 *o, s16 p0, s16 p1)
{
    o->mB4C = p0;
    o->mB4E = p1;
}
