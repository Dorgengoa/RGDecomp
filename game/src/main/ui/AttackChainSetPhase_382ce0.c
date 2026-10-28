/* rgp:protos */
#define RGP_SELF_AttackChainSetPhase_382ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x8. */

typedef struct Obj_FUN_00382ce0 {
    u8 pad000[0x8];
    s16 field;         /* +0x8 */
} Obj_FUN_00382ce0;

void AttackChainSetPhase_382ce0(Obj_FUN_00382ce0 *o, s16 value)
{
    o->field = value;
}
