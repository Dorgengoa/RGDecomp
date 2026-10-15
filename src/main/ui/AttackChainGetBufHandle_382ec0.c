#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_00382ec0 {
    s32 field;         /* +0x00 */
} Obj_FUN_00382ec0;

s32 AttackChainGetBufHandle_382ec0(Obj_FUN_00382ec0 *o)
{
    return o->field;
}
