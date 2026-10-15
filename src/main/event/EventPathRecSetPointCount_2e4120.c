#include "types.h"

/* Write the s16 at +0x18. */

typedef struct Obj_FUN_002e4120 {
    u8 pad000[0x18];
    s16 field;         /* +0x18 */
} Obj_FUN_002e4120;

void EventPathRecSetPointCount_2e4120(Obj_FUN_002e4120 *o, s16 value)
{
    o->field = value;
}
