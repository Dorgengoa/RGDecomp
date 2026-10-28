/* rgp:protos */
#define RGP_SELF_ClsnInfoSetPstr_228180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00228180 {
    u8 pad000[0x10];
    f32 m10;         /* +0x10 */
    f32 m14;         /* +0x14 */
} Obj_FUN_00228180;

void ClsnInfoSetPstr_228180(Obj_FUN_00228180 *o, f32 f0, f32 f1)
{
    o->m10 = f0;
    o->m14 = f1;
}
