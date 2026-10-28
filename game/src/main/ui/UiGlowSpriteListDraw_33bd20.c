/* rgp:protos */
#define RGP_SELF_UiGlowSpriteListDraw_33bd20 1
#include "port/game_protos.h"
#line 1
/* PARK s17c: 1 round trip. Particle/decal-billboard renderer setup: configs
   a draw context via a long chain of FUN_0013eXXX setters, then per-active
   entry (arg0+0x10, stride 0x18) issues two textured-quad draws via
   GsPktSetXYZPixel_13f110 offset by a scaled unk14. 143/136 words (+28 bytes). Not
   isolated further within budget. */
#include "types.h"

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

typedef struct {
    s16 x;
    s16 y;
    s16 on;
    u8 pad6[6];
    f32 fC;
    u8 pad10[4];
    f32 f14;
} Ent;

typedef struct {
    s32 tex;
    s32 f4;
    s16 f8;
    s16 xA;
    s16 yC;
    s16 nE;
    Ent ent[1];
} Obj;

void UiGlowSpriteListDraw_33bd20(Obj *arg0)
{
    f32 s;
    s32 d;
    s32 h;
    s32 g;
    Ent *e;
    s32 i;

    if (arg0->f8 != 0 && arg0->nE > 0) {
        h = GetDrawCtx_15de80();
        DrawListAddTexLoad_1418c0(h, arg0->f4, 1.0f);
        g = ((s32)DrawListBeginPrim_141b00(h));
        GsPktSetOriginMode_13e2f0(g, 0);
        GsPktSetTextured_13e400(g, 1);
        GsPktSetAlphaBlend_13e500(g, 1);
        GsPktSetBlendMode_13e4f0(g, 2);
        GsPktEnableAlphaTest_13e4d0(g, 1);
        GsPktSetGouraud_13e3b0(g, 1);
        GsPktSetTexFilter_13e3d0(g, 1);
        GsPktSetZWriteMask_13e430(g, 1);
        GsPktSetFrameMask_13e420(g, -1);
        GsPktEnableZTest_13e460(g, 0);
        GsPktSetUseUV_13e3e0(g, 1);
        e = arg0->ent;
        i = 0;
        while (i < arg0->nE) {
            if (e->on != 0) {
                s = 128.0f * e->fC;
                GsPktOpenPrim_13f730(g, 6);
                GsPktSetTexture_13ec00(g, arg0->tex);
                d = (s32)(33.0f * e->f14);
                GsPktSetRGBAQ_13ee40(g, 0x60, 0xA0, 0x60, (s32)s);
                GsPktSetUV_13ed60(g, 0x38, 0x98);
                GsPktSetXYZPixel_13f110(g, arg0->xA + e->x, arg0->yC + e->y, 0);
                GsPktSetUV_13ed60(g, 0x59, 0xB9);
                GsPktSetXYZPixel_13f110(g, d + (arg0->xA + e->x), d + (arg0->yC + e->y), 0);
                GsPktClose_13f5b0(g);
            }
            i++;
            e++;
        }
        DrawListEndPrim_141a20(h);
    }
}
