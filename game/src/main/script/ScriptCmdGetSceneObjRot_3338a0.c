/* rgp:protos */
#define RGP_SELF_ScriptCmdGetSceneObjRot_3338a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S8_003338a0 {
    s32 a;
    s32 b;
} S8_003338a0;

typedef struct V16_003338a0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} __attribute__((aligned(16))) V16_003338a0;

typedef struct Rec_003338a0 {
    u8 pad000[0x190];
    V16_003338a0 m190;
} Rec_003338a0;

extern f32 D_0047F4C0;
extern f32 D_0047F4C4;
extern f32 D_0047F4C8;
extern f32 D_0047F4CC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdGetSceneObjRot_3338a0(u8 *a0, s32 mode)
{
    V16_003338a0 v __attribute__((aligned(16)));
    S8_003338a0 *p;
    s32 id;
    Rec_003338a0 *r;

    p = (S8_003338a0 *)a0;
    if (mode != 4) {
        return 0;
    }
    id = ScriptSlotGetInt_3348b0((u8 *)p++);
    v.x = D_0047F4C0;
    v.y = D_0047F4C4;
    v.z = D_0047F4C8;
    v.w = D_0047F4CC;
    r = ((Rec_003338a0 *)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id));
    if (r == 0) {
        return 0;
    }
    v = r->m190;
    ScriptSlotStoreVec3_334790((u8 *)p, &v);
    return 1;
}
