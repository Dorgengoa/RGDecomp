#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0010a400 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_0010a400;

void sceGifPkInit_10a400(Obj_FUN_0010a400 *o, s32 p0)
{
    o->m00 = p0;
    o->m08 = 0;
    o->m04 = p0;
}
