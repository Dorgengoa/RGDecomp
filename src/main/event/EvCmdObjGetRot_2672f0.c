#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct V4 { f32 x, y, z, w; } __attribute__((aligned(16))) V4;

typedef struct T {
    u8 pad0000[0x190];
    V4 m190;
} T;

extern s32  ScriptGetInt_26a2a0(R8 *p);
extern T   *EventSceneGetObj_2676e0(s32 v);
extern void ScriptSetRefFloat_26a1c0(R8 *p, f32 f);

s32 EvCmdObjGetRot_2672f0(R8 *q)
{
    T *r;
    V4 v;

    r = EventSceneGetObj_2676e0(ScriptGetInt_26a2a0(q++));
    if (r == 0) {
        return 0;
    }
    v = r->m190;
    ScriptSetRefFloat_26a1c0(q++, v.x);
    ScriptSetRefFloat_26a1c0(q++, v.y);
    ScriptSetRefFloat_26a1c0(q++, v.z);
    return 1;
}
