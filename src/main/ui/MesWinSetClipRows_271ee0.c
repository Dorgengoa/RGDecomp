#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00271ee0 {
    u8 pad000[0x50];
    s16 m50;         /* +0x50 */
    s16 m52;         /* +0x52 */
} Obj_FUN_00271ee0;

void MesWinSetClipRows_271ee0(Obj_FUN_00271ee0 *o, s16 p0, s16 p1)
{
    o->m50 = p0;
    o->m52 = p1;
}
