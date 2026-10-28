/* rgp:protos */
#define RGP_SELF_AttackChainGetAppliedHitCount_382e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xC. */

typedef struct Obj_FUN_00382e80 {
    u8 pad000[0xC];
    s16 field;         /* +0xC */
} Obj_FUN_00382e80;

s16 AttackChainGetAppliedHitCount_382e80(Obj_FUN_00382e80 *o)
{
    return o->field;
}
