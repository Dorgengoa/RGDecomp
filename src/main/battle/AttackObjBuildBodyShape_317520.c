#include "types.h"

typedef struct Obj_FUN_00317520 {
    u8  pad000[0x7C];
    s32 flags07C;
    u8  pad080[0x48];
    f32 f0C8;
} Obj_FUN_00317520;

extern s32 AttackObjBuildWorldHitSphere_3174a0(Obj_FUN_00317520 *, void *);

s32 AttackObjBuildBodyShape_317520(Obj_FUN_00317520 *o, void *b)
{
    if (!(o->f0C8 < 0.0f)) return 0;
    if (!(o->flags07C & 0x2)) return 0;
    return AttackObjBuildWorldHitSphere_3174a0(o, b);
}
