#include "types.h"

typedef struct Obj_FUN_00318a50 {
    u8  pad000[0x7C];
    s32 flags07C;
    u8  pad080[0x48];
    f32 f0C8;
} Obj_FUN_00318a50;

extern s32 NodeRefObjBuildHitShapeList_318650(Obj_FUN_00318a50 *, void *);

s32 NodeRefObjBuildBodyShape_318a50(Obj_FUN_00318a50 *o, void *b)
{
    if (!(o->f0C8 < 0.0f)) return 0;
    if (!(o->flags07C & 0x2)) return 0;
    return NodeRefObjBuildHitShapeList_318650(o, b);
}
