/* rgp:protos */
#define RGP_SELF_UskStackClear_42e460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0042e460 {
    u8 pad000[0x20];
    s32 m20;         /* +0x20 */
    s32 m24;         /* +0x24 */
    s32 m28;         /* +0x28 */
} Obj_FUN_0042e460;

void UskStackClear_42e460(Obj_FUN_0042e460 *o)
{
    o->m20 = 0;
    o->m24 = 0;
    o->m28 = 0;
}
