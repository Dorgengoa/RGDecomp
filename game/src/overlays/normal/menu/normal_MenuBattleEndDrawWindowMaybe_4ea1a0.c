/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndDrawWindowMaybe_4ea1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EA1A0 -- builds one window: pull the 4 floats out of the
 * func_290460 record, look the caption up with func_159FB0, then walk the
 * whole func_13Exxx setter list off the func_141B00 handle, scaling the four
 * floats by 128.0f for func_13EE40. */

typedef struct Ea1Rec {
    u8   pad000[4];
    u8   f004[0x20 - 0x4];
    struct Ea1Ent *f020;
    u8   pad024[0x30 - 0x24];
    f32  f030[4];
} Ea1Rec;

typedef struct Ea1Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s16 f008;
    s16 f00A;
    u8  pad00C[0x1C - 0xC];
    u16 f01C;
} Ea1Ent;

typedef struct Ea1Cap {
    s16 f000;
} Ea1Cap;

typedef struct Ea1Obj {
    u8 pad000[0x14];
    u8 f014[0x100 - 0x14];
} Ea1Obj;

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

void normal_MenuBattleEndDrawWindowMaybe_4ea1a0(Ea1Obj *p)
{
    f32 fv[4] __attribute__((aligned(16)));
    s32 iv[4] __attribute__((aligned(16)));
    void *a;
    void *b;
    Ea1Rec *r;
    Ea1Ent *e;
    Ea1Cap *c;
    void *w;
    s32 i;

    a = GetDrawCtx_15de80();
    b = GetDrawCtxNameTable_15de40();
    r = ((Ea1Rec *)UiFindWidget_290460(p->f014, 1));
    e = r->f020;
    for (i = 0; i < 4; i++) {
        fv[i] = r->f030[i];
    }
    c = ((Ea1Cap *)NameTableFindByName_159fb0(b, r->f004, 0x32D));
    if (c != NULL) {
        DrawListAddTexLoad_1418c0(a, c->f000, 1.0f);
    }
    w = DrawListBeginPrim_141b00(a);
    GsPktSetBlendMode_13e4f0(w, 1);
    if ((e->f01C & 1) != 0) {
        GsPktSetBlendMode_13e4f0(w, 2);
    }
    GsPktSetAlphaBlend_13e500(w, 1);
    GsPktSetAntialias_13e390(w, 0);
    GsPktEnableAlphaTest_13e4d0(w, 1);
    GsPktEnableZTest_13e460(w, 0);
    GsPktSetTextured_13e400(w, 1);
    GsPktSetUseUV_13e3e0(w, 1);
    GsPktSetOriginMode_13e2f0(w, 0);
    if ((e->f01C & 2) != 0) {
        GsPktSetTexFilter_13e3d0(w, 1);
    } else {
        GsPktSetTexFilter_13e3d0(w, 0);
    }
    GsPktSetZWriteMask_13e430(w, 0);
    GsPktSetGouraud_13e3b0(w, 0);
    GsPktOpenPrim_13f730(w, 6);
    GsPktSetTexture_13ec00(w, c);
    for (i = 0; i < 4; i++) {
        iv[i] = (s32)(128.0f * fv[i]);
    }
    GsPktSetRGBAQ_13ee40(w, iv[0], iv[1], iv[2], iv[3]);
    GsPktSetUV_13ed60(w, e->f008, e->f00A);
    GsPktSetXYZPixel_13f110(w, e->f000, e->f002, 0);
    GsPktSetUV_13ed60(w, e->f008 + 1, e->f00A + 1);
    GsPktSetXYZPixel_13f110(w, e->f000 + e->f004, e->f002 + e->f006, 0);
    GsPktClose_13f5b0(w);
    DrawListEndPrim_141a20(a);
}
