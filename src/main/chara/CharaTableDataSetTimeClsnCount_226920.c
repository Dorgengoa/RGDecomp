#include "types.h"

/* Write the s16 at +0x28. */

typedef struct Obj_FUN_00226920 {
    u8 pad000[0x28];
    s16 field;         /* +0x28 */
} Obj_FUN_00226920;

void CharaTableDataSetTimeClsnCount_226920(Obj_FUN_00226920 *o, s16 value)
{
    o->field = value;
}
