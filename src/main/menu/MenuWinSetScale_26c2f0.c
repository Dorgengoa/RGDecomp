#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0026c2f0 {
    u8 pad000[0x7C];
    f32 m7C;         /* +0x7C */
    f32 m80;         /* +0x80 */
} Obj_FUN_0026c2f0;

void MenuWinSetScale_26c2f0(Obj_FUN_0026c2f0 *o, f32 f0, f32 f1)
{
    o->m7C = f0;
    o->m80 = f1;
}
