/* rgp:protos */
#define RGP_SELF_SaveProgressReset_373670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00373670 {
    u8 pad000[0x520];
    s32 m520;         /* +0x520 */
    s32 m524;         /* +0x524 */
} Obj_FUN_00373670;

void SaveProgressReset_373670(Obj_FUN_00373670 *o)
{
    o->m524 = 0;
    o->m520 = 0;
}
