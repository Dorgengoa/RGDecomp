#include "types.h"

/* Write the s16 at +0xA2E. */

typedef struct Obj_FUN_00213820 {
    u8 pad000[0xA2E];
    s16 field;         /* +0xA2E */
} Obj_FUN_00213820;

void CharaSetBaseActionMode_213820(Obj_FUN_00213820 *o, s16 value)
{
    o->field = value;
}
