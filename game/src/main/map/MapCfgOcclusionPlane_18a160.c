/* rgp:protos */
#define RGP_SELF_MapCfgOcclusionPlane_18a160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Q_FUN_0018a160 {
    u8 pad000[0xC];
    f32 f0C;
} Q_FUN_0018a160;

typedef struct Obj_FUN_0018a160 Obj_FUN_0018a160;
typedef struct G_FUN_0018a160 G_FUN_0018a160;

extern G_FUN_0018a160 *D_00481250;
/*rgp*/
/*rgp*/

s32 MapCfgOcclusionPlane_18a160(Obj_FUN_0018a160 *o)
{
    Q_FUN_0018a160 q[4] __attribute__((aligned(16)));
    Q_FUN_0018a160 *p;
    s32 i;

    for (i = 0; i < 4; i++) {
        p = &q[i];
        VariantReadVec3_15f6c0(p, o);
        p->f0C = 1.0f;
        o = (Obj_FUN_0018a160 *)((u8 *)o + 0x18);
    }
    OcclusionPlaneAdd_189280(D_00481250, q);
    return 1;
}
