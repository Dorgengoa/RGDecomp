#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_002138e0 {
    u8 pad000[0xA60];
    f32 mA60;         /* +0xA60 */
    f32 mA64;         /* +0xA64 */
} Obj_FUN_002138e0;

void CharaSetHoverParams_2138e0(Obj_FUN_002138e0 *o, f32 f0, f32 f1)
{
    o->mA60 = f0;
    o->mA64 = f1;
}
