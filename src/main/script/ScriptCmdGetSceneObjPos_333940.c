#include "types.h"

typedef struct S8_00333940 {
    s32 a;
    s32 b;
} S8_00333940;

typedef struct V16_00333940 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} __attribute__((aligned(16))) V16_00333940;

typedef struct Rec_00333940 {
    u8 pad000[0x180];
    V16_00333940 m180;
} Rec_00333940;

extern f32 D_0047F4B0;
extern f32 D_0047F4B4;
extern f32 D_0047F4B8;
extern f32 D_0047F4BC;

extern s32 ScriptSlotGetInt_3348b0(u8 *p);
extern void *GetCurrentScene_1f5be0(void);
extern Rec_00333940 *ObjRecGetLiveObject_1c4a90(void *a, s32 id);
extern void ScriptSlotStoreVec3_334790(u8 *p, V16_00333940 *v);

s32 ScriptCmdGetSceneObjPos_333940(u8 *a0, s32 mode)
{
    V16_00333940 v;
    S8_00333940 *p;
    s32 id;
    Rec_00333940 *r;

    p = (S8_00333940 *)a0;
    if (mode != 4) {
        return 0;
    }
    id = ScriptSlotGetInt_3348b0((u8 *)p++);
    v.x = D_0047F4B0;
    v.y = D_0047F4B4;
    v.z = D_0047F4B8;
    v.w = D_0047F4BC;
    r = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id);
    if (r == 0) {
        return 0;
    }
    v = r->m180;
    ScriptSlotStoreVec3_334790((u8 *)p, &v);
    return 1;
}
