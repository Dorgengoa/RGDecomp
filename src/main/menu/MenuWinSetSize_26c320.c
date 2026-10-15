#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0026c320 {
    u8 pad000[0x64];
    s32 m64;         /* +0x64 */
    s32 m68;         /* +0x68 */
} Obj_FUN_0026c320;

void MenuWinSetSize_26c320(Obj_FUN_0026c320 *o, s32 p0, s32 p1)
{
    o->m64 = p0;
    o->m68 = p1;
}
