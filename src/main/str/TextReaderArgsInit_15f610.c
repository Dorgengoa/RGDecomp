#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0015f610 {
    u8 pad000[0xC];
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
    s32 m14;         /* +0x14 */
} Obj_FUN_0015f610;

void TextReaderArgsInit_15f610(Obj_FUN_0015f610 *o, s32 p0, s32 p1)
{
    o->m14 = p0;
    o->m10 = p1;
    o->m0C = 0;
}
