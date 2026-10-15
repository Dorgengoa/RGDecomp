#include "types.h"

/* Read the s16 at +0xA. */

typedef struct Obj_FUN_00382ea0 {
    u8 pad000[0xA];
    s16 field;         /* +0xA */
} Obj_FUN_00382ea0;

s16 AttackChainGetHitCount_382ea0(Obj_FUN_00382ea0 *o)
{
    return o->field;
}
