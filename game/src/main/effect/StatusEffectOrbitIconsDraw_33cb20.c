/* rgp:protos */
#define RGP_SELF_StatusEffectOrbitIconsDraw_33cb20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

typedef struct {
    V4 r[4];
} M4;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f64 D_0047D190;
extern f32 D_0047D850;
extern f32 D_0047F630;
extern f32 D_0047F634;
extern f32 D_0047F638;
extern f32 D_0047F63C;
extern u8 D_00462628[];

void StatusEffectOrbitIconsDraw_33cb20(u8 *arg0)
{
    V4 pos __attribute__((aligned(16)));
    V4 v __attribute__((aligned(16)));
    V4 e __attribute__((aligned(16)));
    M4 m __attribute__((aligned(16)));
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    u8 *c;
    s32 ctx;
    s32 pk;
    s32 tex;
    f32 r;
    s32 al;
    s32 i;
    f32 ang;

    c = ((u8 *)ObjRecGetLiveObject_1c4a90(((s32)GetStaticScene_1c6c70()), *(s16 *)(arg0 + 0x14)));
    if (c == 0) {
        return;
    }
    *(u128 *)&pos = *(u128 *)(c + 0x180);
    pos.y += (f32)(5.0 + dpmul(D_0047D190, (f64)*(f32 *)(c + 0x4CC)));
    if (*(s16 *)(arg0 + 0x12) == 0) {
        pos.y -= 5.0f;
    }
    ctx = GetDrawCtx_15de80();
    pk = ((s32)DrawListBeginPrim_141b00(ctx));
    tex = ((s32)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00462628, 0x2A6));
    GsPktSetOriginMode_13e2f0(pk, 1);
    GsPktSetTextured_13e400(pk, 1);
    GsPktSetAlphaBlend_13e500(pk, 1);
    GsPktSetBlendMode_13e4f0(pk, 1);
    GsPktEnableAlphaTest_13e4d0(pk, 1);
    GsPktSetGouraud_13e3b0(pk, 0);
    GsPktSetTexFilter_13e3d0(pk, 1);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktEnableZTest_13e460(pk, 1);
    r = 5.0f;
    al = 0x40;
    if (*(s16 *)(arg0 + 0x12) == 3) {
        r = 4.0f;
        al = 0;
    }
    v.x = D_0047F630;
    v.y = D_0047F634;
    v.z = D_0047F638;
    v.w = D_0047F63C;
    ang = *(f32 *)(arg0 + 0x90);
    for (i = 0; i < 3; i++) {
        MtxRotY_13ce20(&m, ang);
        ang += D_0047D850;
        MtxMulVec4_10a8c0(&e, &m, &v);
        VecScale_13be00(&e, &e, 5.0f);
        sceVu0AddVector(&e, &e, &pos);
        if (CameraProjectBillboardRect_15cde0(&a, &b, r, r, &e) != 0) {
            GsPktOpenPrim_13f730(pk, 6);
            GsPktSetTexture_13ec00(pk, tex);
            GsPktSetUV_13ed60(pk, 0x40, al);
            GsPktSetRGBAQ_13ee40(pk, 0x80, 0x80, 0x80, 0x80);
            GsPktSetXYZVecI_13eeb0(pk, &a);
            GsPktSetUV_13ed60(pk, 0x7F, al + 0x3F);
            GsPktSetRGBAQ_13ee40(pk, 0x80, 0x80, 0x80, 0x80);
            GsPktSetXYZVecI_13eeb0(pk, &b);
            GsPktClose_13f5b0(pk);
        }
    }
    DrawListEndPrim_141a20(ctx);
}
