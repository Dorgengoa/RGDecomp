/* rgp:protos */
#define RGP_SELF_SrtSetVelocity_1c7190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001c7190 {
    u8 pad000[0x30];
    f32 m30;         /* +0x30 */
    f32 m34;         /* +0x34 */
    f32 m38;         /* +0x38 */
    s32 m3C;         /* +0x3C */
} Obj_FUN_001c7190;

void SrtSetVelocity_1c7190(Obj_FUN_001c7190 *o, f32 f0, f32 f1, f32 f2)
{
    o->m30 = f0;
    o->m34 = f1;
    o->m38 = f2;
    o->m3C = 0;
}
