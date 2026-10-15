#include "types.h"

typedef struct Obj_FUN_00318aa0 {
    u8  pad000[0x7C];
    s32 flags07C;
    u8  pad080[0x48];
    f32 f0C8;
} Obj_FUN_00318aa0;

extern s32 NodeRefObjBuildHitShapeList_318650(Obj_FUN_00318aa0 *, void *);

s32 NodeRefObjBuildAttackShape_318aa0(Obj_FUN_00318aa0 *o, void *b)
{
    if (!(o->f0C8 < 0.0f)) return 0;
    if (!(o->flags07C & 0x1)) return 0;
    return NodeRefObjBuildHitShapeList_318650(o, b);
}
