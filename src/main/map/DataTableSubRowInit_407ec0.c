#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00407ec0 {
    u8 m00;         /* +0x0 */
    u8 m01;         /* +0x1 */
    u8 m02;         /* +0x2 */
    u8 pad003[0x1];
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_00407ec0;

void DataTableSubRowInit_407ec0(Obj_FUN_00407ec0 *o)
{
    o->m00 = 0;
    o->m01 = 0;
    o->m02 = 0;
    o->m04 = 0;
    o->m08 = 0;
}
