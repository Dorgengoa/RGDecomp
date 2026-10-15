#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0029f9b0 {
    u8 pad000[0x60];
    s16 m60;         /* +0x60 */
    s16 m62;         /* +0x62 */
    s16 m64;         /* +0x64 */
} Obj_FUN_0029f9b0;

void MenuSetGridSel_29f9b0(Obj_FUN_0029f9b0 *o, s16 p0, s16 p1, s16 p2)
{
    o->m60 = p0;
    o->m62 = p1;
    o->m64 = p2;
}
