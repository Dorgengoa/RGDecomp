#include "types.h"

/* Guard pair over an indirect table: the count is at +0x0 and the array
   POINTER at +0x4, so the compute block starts by loading the pointer -- and
   that load is what fills the bounds guard's delay slot here, where the other
   members of the class put the index shift there. */

typedef struct Owner00152fd0 {
    s32 count;         /* +0x00 */
    s32 *list;         /* +0x04 */
} Owner00152fd0;

s32 ArrayGetChecked_152fd0(Owner00152fd0 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < o->count;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return o->list[index];
}
