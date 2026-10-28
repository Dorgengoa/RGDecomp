/* rgp:protos */
#define RGP_SELF_AttackObjBaseBuildAttackShape_318160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00318160 {
    u8  pad000[0x7C];
    s32 flags07C;
    u8  pad080[0x48];
    f32 f0C8;
} Obj_FUN_00318160;

/*rgp*/

s32 AttackObjBaseBuildAttackShape_318160(Obj_FUN_00318160 *o, void *b, int rgp_a2, int rgp_a3)
{
    if (!(o->f0C8 < 0.0f)) return 0;
    if (!(o->flags07C & 0x1)) return 0;
    return ((s32)AttackObjBaseBuildHitSphere_318090(o, b, (int)rgp_a2, (int)rgp_a3));
}
