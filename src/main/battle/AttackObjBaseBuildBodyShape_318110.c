#include "types.h"

typedef struct Obj_FUN_00318110 {
    u8  pad000[0x7C];
    s32 flags07C;
    u8  pad080[0x48];
    f32 f0C8;
} Obj_FUN_00318110;

extern s32 AttackObjBaseBuildHitSphere_318090(Obj_FUN_00318110 *, void *);

s32 AttackObjBaseBuildBodyShape_318110(Obj_FUN_00318110 *o, void *b)
{
    if (!(o->f0C8 < 0.0f)) return 0;
    if (!(o->flags07C & 0x2)) return 0;
    return AttackObjBaseBuildHitSphere_318090(o, b);
}
