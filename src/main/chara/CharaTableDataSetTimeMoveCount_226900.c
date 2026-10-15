#include "types.h"

/* Write the s16 at +0x2C. */

typedef struct Obj_FUN_00226900 {
    u8 pad000[0x2C];
    s16 field;         /* +0x2C */
} Obj_FUN_00226900;

void CharaTableDataSetTimeMoveCount_226900(Obj_FUN_00226900 *o, s16 value)
{
    o->field = value;
}
