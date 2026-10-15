#include "types.h"

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

extern void FrameTransformPoint_148f60(s32, Vec *, Vec *);
extern s32 ModelGetFrame_1511f0(s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern void ScriptSlotStoreFloatRef_2cc8e0(s32, f32);
extern f32 ScriptSlotGetFloat_2cc9a0(s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern u8 D_004DB920[0x400];

s32 AiCmdObjNodeWorldPos_2ca050(s64 *arg0, s32 arg1)
{
    Vec v;
    s32 a;
    s32 b;
    s32 r;
    f32 x;
    f32 y;
    f32 z;
    u8 *q;
    u32 n;

    a = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    b = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    x = 0.0f;
    y = x;
    z = x;
    if (arg1 == 8) {
        x = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
        y = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
        z = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    }
    q = (u8 *)&v;
    n = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    v.z = z;
    v.x = x;
    v.y = y;
    r = ObjRecGetLiveObject_1c4a90(*(s32 *)D_004DB920, a);
    if (r == 0) {
        return 0;
    }
    r = ModelGetFrame_1511f0(r, b);
    if (r == 0) {
        return 0;
    }
    FrameTransformPoint_148f60(r, &v, &v);
    ScriptSlotStoreFloatRef_2cc8e0((s32)arg0++, v.x);
    ScriptSlotStoreFloatRef_2cc8e0((s32)arg0++, v.y);
    ScriptSlotStoreFloatRef_2cc8e0((s32)arg0++, v.z);
    return 1;
}
