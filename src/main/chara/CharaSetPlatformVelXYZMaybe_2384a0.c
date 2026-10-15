#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_002384a0 {
    u8 pad000[0xE0];
    f32 mE0;         /* +0xE0 */
    f32 mE4;         /* +0xE4 */
    f32 mE8;         /* +0xE8 */
    s32 mEC;         /* +0xEC */
} Obj_FUN_002384a0;

void CharaSetPlatformVelXYZMaybe_2384a0(Obj_FUN_002384a0 *o, f32 f0, f32 f1, f32 f2)
{
    o->mE0 = f0;
    o->mE4 = f1;
    o->mE8 = f2;
    o->mEC = 0;
}
