/* rgp:protos */
#define RGP_SELF_StatusEffectHitIconsDraw_33c660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct V4 {
    f32 x, y, z, w;
} V4;

typedef struct P2 {
    f32 x, y;
} P2;

typedef struct T3 {
    P2 p[3];
} T3;

typedef struct Obj {
    u8 pad0[0x10];
    s16 x10;
    u8 pad12[2];
    s16 x14;
    u8 pad16[0x30 - 0x16];
    V4 v30[6];
    f32 x90[6];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00462618[];
extern u8 D_00452EA0[];

void StatusEffectHitIconsDraw_33c660(Obj *o)
{
    u128 q;
    T3 t __attribute__((aligned(16)));
    V4 pos __attribute__((aligned(16)));
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    u8 *v;
    s32 w;
    s32 r;
    s32 s;
    s32 i;
    s32 k;
    P2 *tp;
    f32 y;
    f32 x;

    if (o->x10 == 0) {
        return;
    }
    v = ((u8 *)ObjRecGetLiveObject_1c4a90(((s32)GetStaticScene_1c6c70()), o->x14));
    if (v == NULL) {
        return;
    }
    q = *(u128 *)(v + 0x180);
    w = GetDrawCtx_15de80();
    r = ((s32)DrawListBeginPrim_141b00(w));
    s = ((s32)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00462618, -1));
    GsPktSetOriginMode_13e2f0(r, 1);
    GsPktSetTextured_13e400(r, 1);
    GsPktSetAlphaBlend_13e500(r, 1);
    GsPktSetBlendMode_13e4f0(r, 2);
    GsPktEnableAlphaTest_13e4d0(r, 1);
    GsPktSetGouraud_13e3b0(r, 0);
    GsPktSetTexFilter_13e3d0(r, 1);
    GsPktSetZWriteMask_13e430(r, 1);
    GsPktEnableZTest_13e460(r, 1);
    t = *(T3 *)D_00452EA0;
    for (i = 0; i < 6; i++) {
        sceVu0CopyVector(&pos, &q);
        pos.x = pos.x + 10.0f * o->v30[i].x;
        pos.y = pos.y + 40.0f * o->v30[i].y;
        pos.z = pos.z + 10.0f * o->v30[i].z;
        pos.w = 1.0f;
        k = o->x90[i] / 3.0f;
        if (CameraProjectBillboardRect_15cde0(&a, &b, 10.0f, 10.0f, &pos) == 0) {
            continue;
        }
        GsPktOpenPrim_13f730(r, 6);
        GsPktSetTexture_13ec00(r, s);
        tp = (P2 *)((u32)&t.p[k]);
        y = tp->y;
        x = tp->x;
        GsPktSetUV_13ed60(r, x, y);
        GsPktSetRGBAQ_13ee40(r, 0xE4, 0xE4, 0xE4, 0xFA);
        GsPktSetXYZVecI_13eeb0(r, &a);
        GsPktSetUV_13ed60(r, 63.0f + x, 63.0f + y);
        GsPktSetRGBAQ_13ee40(r, 0xE4, 0xE4, 0xE4, 0xFA);
        GsPktSetXYZVecI_13eeb0(r, &b);
        GsPktClose_13f5b0(r);
    }
    DrawListEndPrim_141a20(w);
}
