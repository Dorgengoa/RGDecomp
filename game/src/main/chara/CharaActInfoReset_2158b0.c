/* rgp:protos */
#define RGP_SELF_CharaActInfoReset_2158b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_002158b0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_002158b0;

void CharaActInfoReset_2158b0(Obj_FUN_002158b0 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m08 = 0;
}
