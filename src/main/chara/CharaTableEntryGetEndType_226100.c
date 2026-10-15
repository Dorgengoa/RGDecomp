#include "types.h"

/* Read the s16 at +0x3A. */

typedef struct Obj_FUN_00226100 {
    u8 pad000[0x3A];
    s16 field;         /* +0x3A */
} Obj_FUN_00226100;

s16 CharaTableEntryGetEndType_226100(Obj_FUN_00226100 *o)
{
    return o->field;
}
