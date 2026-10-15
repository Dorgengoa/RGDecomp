#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_003761b0 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s16 m04;         /* +0x4 */
    s16 m06;         /* +0x6 */
    s32 m08;         /* +0x8 */
} Obj_FUN_003761b0;

void SaveResultClear_3761b0(Obj_FUN_003761b0 *o)
{
    o->m00 = 0;
    o->m02 = 0;
    o->m04 = 0;
    o->m06 = 0;
    o->m08 = 0;
}
