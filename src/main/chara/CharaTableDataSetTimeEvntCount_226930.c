#include "types.h"

/* Write the s16 at +0x26. */

typedef struct Obj_FUN_00226930 {
    u8 pad000[0x26];
    s16 field;         /* +0x26 */
} Obj_FUN_00226930;

void CharaTableDataSetTimeEvntCount_226930(Obj_FUN_00226930 *o, s16 value)
{
    o->field = value;
}
