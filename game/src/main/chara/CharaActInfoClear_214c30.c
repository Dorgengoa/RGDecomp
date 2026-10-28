/* rgp:protos */
#define RGP_SELF_CharaActInfoClear_214c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00214c30 {
    u8 pad000[0x428];
    s32 m428;         /* +0x428 */
    u8 pad42C[0x154];
    s32 m580;         /* +0x580 */
    s32 m584;         /* +0x584 */
    s32 m588;         /* +0x588 */
} Obj_FUN_00214c30;

void CharaActInfoClear_214c30(Obj_FUN_00214c30 *o)
{
    o->m580 = 0;
    o->m584 = 0;
    o->m588 = 0;
    o->m428 = 0;
}
