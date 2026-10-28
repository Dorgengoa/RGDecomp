/* rgp:protos */
#define RGP_SELF_BlockHeapReset_1c2770 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001c2770 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    u8 pad008[0x14];
    s32 m1C;         /* +0x1C */
    s32 m20;         /* +0x20 */
    s32 m24;         /* +0x24 */
} Obj_FUN_001c2770;

void BlockHeapReset_1c2770(Obj_FUN_001c2770 *o)
{
    o->m24 = 0;
    o->m00 = 0;
    o->m04 = 0;
    o->m1C = 0;
    o->m20 = 0;
}
