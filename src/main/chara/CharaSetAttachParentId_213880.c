#include "types.h"

/* Write the s32 at +0xB20. */

typedef struct Obj_FUN_00213880 {
    u8 pad000[0xB20];
    s32 field;         /* +0xB20 */
} Obj_FUN_00213880;

void CharaSetAttachParentId_213880(Obj_FUN_00213880 *o, s32 value)
{
    o->field = value;
}
