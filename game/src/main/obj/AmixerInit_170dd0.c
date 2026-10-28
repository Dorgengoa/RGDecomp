/* rgp:protos */
#define RGP_SELF_AmixerInit_170dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00170dd0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
} Obj_FUN_00170dd0;

void AmixerInit_170dd0(Obj_FUN_00170dd0 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m10 = 0;
    o->m08 = 0;
    o->m0C = 0;
}
