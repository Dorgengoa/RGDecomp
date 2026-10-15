#include "types.h"

/* Write the s32 at +0x150. */

typedef struct Obj_FUN_002ea1d0 {
    u8 pad000[0x150];
    s32 field;         /* +0x150 */
} Obj_FUN_002ea1d0;

void EventObjMgrSetHeap_2ea1d0(Obj_FUN_002ea1d0 *o, s32 value)
{
    o->field = value;
}
