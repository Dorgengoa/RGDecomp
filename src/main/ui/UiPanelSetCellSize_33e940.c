#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0033e940 {
    u8 pad000[0x30];
    s32 m30;         /* +0x30 */
    s32 m34;         /* +0x34 */
} Obj_FUN_0033e940;

void UiPanelSetCellSize_33e940(Obj_FUN_0033e940 *o, s32 p0, s32 p1)
{
    o->m30 = p0;
    o->m34 = p1;
}
