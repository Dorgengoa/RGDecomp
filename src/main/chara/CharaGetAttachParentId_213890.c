#include "types.h"

/* Read the s32 at +0xB20. */

typedef struct Obj_FUN_00213890 {
    u8 pad000[0xB20];
    s32 field;         /* +0xB20 */
} Obj_FUN_00213890;

s32 CharaGetAttachParentId_213890(Obj_FUN_00213890 *o)
{
    return o->field;
}
