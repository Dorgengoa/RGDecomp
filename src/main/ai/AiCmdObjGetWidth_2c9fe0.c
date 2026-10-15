#include "types.h"

typedef struct { s32 a, b; } T_002c9fe0;

extern struct { void *p; s32 pad[3]; } D_004DB920;
extern f32 D_0047D240;
extern s32 ScriptSlotGetInt_2cc9c0(T_002c9fe0 *);
extern void *ObjRecGetLiveObject_1c4a90(void *, s32);
extern void ScriptSlotStoreFloatRef_2cc8e0(T_002c9fe0 *, f32);

s32 AiCmdObjGetWidth_2c9fe0(T_002c9fe0 *q)
{
    s32 n;
    void *r;

    n = ScriptSlotGetInt_2cc9c0(q++);
    r = ObjRecGetLiveObject_1c4a90(D_004DB920.p, n);
    if (r == 0) return 0;
    ScriptSlotStoreFloatRef_2cc8e0(q, 2.0f * (D_0047D240 * *(f32 *)((s32)r + 0x4C8)));
    return 1;
}
