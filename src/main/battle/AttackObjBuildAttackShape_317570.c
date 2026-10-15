#include "types.h"

typedef struct Obj_FUN_00317570 {
    u8  pad000[0x7C];
    s32 flags07C;
    u8  pad080[0x48];
    f32 f0C8;
} Obj_FUN_00317570;

extern s32 AttackObjBuildWorldHitSphere_3174a0(Obj_FUN_00317570 *, void *);

s32 AttackObjBuildAttackShape_317570(Obj_FUN_00317570 *o, void *b)
{
    if (!(o->f0C8 < 0.0f)) return 0;
    if (!(o->flags07C & 0x1)) return 0;
    return AttackObjBuildWorldHitSphere_3174a0(o, b);
}
