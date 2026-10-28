/* rgp:protos */
#define RGP_SELF_StreamChanSetVolume_1d7010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001d7010 {
    u8 pad000[0x84];
    f32 m84;         /* +0x84 */
    u8 pad088[0x4];
    f32 m8C;         /* +0x8C */
    s32 m90;         /* +0x90 */
} Obj_FUN_001d7010;

void StreamChanSetVolume_1d7010(Obj_FUN_001d7010 *o, f32 f0)
{
    o->m84 = f0;
    o->m8C = f0;
    o->m90 = 0;
}
