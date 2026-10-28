/* rgp:protos */
#define RGP_SELF_AttackChainGetTimer_382e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x18. */

typedef struct Obj_FUN_00382e70 {
    u8 pad000[0x18];
    f32 field;         /* +0x18 */
} Obj_FUN_00382e70;

f32 AttackChainGetTimer_382e70(Obj_FUN_00382e70 *o)
{
    return o->field;
}
