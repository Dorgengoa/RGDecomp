/* rgp:protos */
#define RGP_SELF_BattleEffectBurstDraw_2d4260 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
typedef struct {
    u8 pad0[0x34];
    s8 unk34;
    u8 pad35[0x40 - 0x35];
} Elem;

typedef struct {
    u8 pad0[0x3BA0];
    s32 unk3BA0;
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
extern u8 D_00461610[0x400];

void BattleEffectBurstDraw_2d4260(u8 *arg0) {
    Obj *o;
    s32 r;
    s32 g;
    Elem *p;
    s32 i;

    p = (Elem *)(arg0 + 0x20);
    for (i = 0; i < 0x40; i++, p++) {
        if (p->unk34 != 0) {
            break;
        }
    }
    if (i < 0x40) {
        o = ((Obj *)GetDrawCtx_15de80());
        r = ((s32)NameTableFindByName_159fb0(o->unk3BA0, D_00461610, -1));
        if (r != 0) {
            g = ((s32)DrawListBeginPrim_141b00(o));
            GsPktSetAlphaBlend_13e500(g, 1);
            GsPktSetBlendMode_13e4f0(g, 2);
            GsPktEnableAlphaTest_13e4d0(g, 1);
            GsPktSetFrameMask_13e420(g, 1);
            GsPktSetZWriteMask_13e430(g, 1);
            GsPktSetTexFilter_13e3d0(g, 1);
            GsPktSetTextured_13e400(g, 1);
            GsPktSetOriginMode_13e2f0(g, 1);
            GsPktSetGouraud_13e3b0(g, 0);
            GsPktEnableZTest_13e460(g, 1);
            GsPktSetZTest_13e450(g, 2);
            GsPktOpenPrim_13f730(g, 3);
            GsPktSetTexture_13ec00(g, r);
            p = (Elem *)(arg0 + 0x20);
            i = 0;
            do {
                if (p->unk34 == 0) {
                    p++;
                } else {
                    BattleEffectParticleDraw_2d4400(arg0, g, p);
                    p++;
                }
                i++;
            } while (i < 0x40);
            GsPktClose_13f5b0(g);
            DrawListEndPrim_141a20(o);
        }
    }
}
