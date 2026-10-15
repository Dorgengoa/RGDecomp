#include "types.h"

/* Write the s32 at +0x0. */

typedef struct Obj_FUN_003237e0 {
    s32 field;         /* +0x00 */
} Obj_FUN_003237e0;

void EntryListSetHeap_3237e0(Obj_FUN_003237e0 *o, s32 value)
{
    o->field = value;
}
