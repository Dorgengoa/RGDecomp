/* rgp:protos */
#define RGP_SELF_AttackChainGetPhase_382eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x8. */

typedef struct Obj_FUN_00382eb0 {
    u8 pad000[0x8];
    s16 field;         /* +0x8 */
} Obj_FUN_00382eb0;

s16 AttackChainGetPhase_382eb0(Obj_FUN_00382eb0 *o)
{
    return o->field;
}
