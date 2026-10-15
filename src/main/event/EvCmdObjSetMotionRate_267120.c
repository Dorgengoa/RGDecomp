#include "types.h"

typedef struct { s32 a, b; } T_00267120;

extern void *ScriptGetInt_26a2a0(T_00267120 *);
extern void *EventSceneGetObj_2676e0(void *);
extern f32 TaggedGetFloat_26a280(T_00267120 *);
extern void ModelObjSetMotionRate_1add50(void *, s32, f32);

s32 EvCmdObjSetMotionRate_267120(T_00267120 *q)
{
    void *a;
    void *b;
    f32 f;

    a = ScriptGetInt_26a2a0(q++);
    b = EventSceneGetObj_2676e0(a);
    if (b == 0) return 0;
    f = TaggedGetFloat_26a280(q);
    ModelObjSetMotionRate_1add50(b, 1, f);
    return 1;
}
