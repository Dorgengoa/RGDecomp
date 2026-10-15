#include "types.h"

/* Write the s16 at +0x40E. */

typedef struct Obj_FUN_00238940 {
    u8 pad000[0x40E];
    s16 field;         /* +0x40E */
} Obj_FUN_00238940;

void CharaSetCollIgnoreMask_238940(Obj_FUN_00238940 *o, s16 value)
{
    o->field = value;
}
