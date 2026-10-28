/* rgp:protos */
#define RGP_SELF_DataTableRowReset_407b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00407b30 {
    u8 m00;         /* +0x0 */
    u8 m01;         /* +0x1 */
    u8 pad002[0x2];
    s32 m04;         /* +0x4 */
} Obj_FUN_00407b30;

void DataTableRowReset_407b30(Obj_FUN_00407b30 *o)
{
    o->m00 = 0;
    o->m01 = 0;
    o->m04 = 0;
}
