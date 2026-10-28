/* rgp:protos */
#define RGP_SELF_AttackChainGetInputCount_382e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x4. */

typedef struct Obj_FUN_00382e90 {
    u8 pad000[0x4];
    s16 field;         /* +0x4 */
} Obj_FUN_00382e90;

s16 AttackChainGetInputCount_382e90(Obj_FUN_00382e90 *o)
{
    return o->field;
}
