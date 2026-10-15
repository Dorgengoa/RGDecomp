#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_003121d0 {
    s32 field;         /* +0x00 */
} Obj_FUN_003121d0;

s32 CharaRefGetBlock_3121d0(Obj_FUN_003121d0 *o)
{
    return o->field;
}
