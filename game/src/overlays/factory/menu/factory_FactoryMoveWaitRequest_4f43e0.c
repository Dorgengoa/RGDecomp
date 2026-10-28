/* rgp:protos */
#define RGP_SELF_factory_FactoryMoveWaitRequest_4f43e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Glob {
    u8    pad00[0x5C];
    u8    f5C;
    u8    pad5D[0x3];
    void *f60;
} Glob;

typedef struct St {
    s32 f00;
    s32 f04;
} St;

typedef struct Buf {
    s32 f00;
    s32 f04;
    u8  pad08[0x8];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x14];
} Buf;                                          /* 0x34 */

extern u8    D_004B2570[0x10];
extern void *D_00484A70;                        /* _gp - 0x700 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMoveWaitRequest_4f43e0(Glob *g)
{
    Buf b __attribute__((aligned(16)));
    St *s;

    s = ((St *)FactoryGetRequestPtr_367ec0());
    if (g->f5C == 1) {
        if (PadIsTriggered_1839f0(D_004B2570, 0x40) != 0 || PadIsTriggered_1839f0(D_004B2570, 0x20) != 0) {
            UiFadeWidgetAlpha_290690(g->f60, 0x51, 0.0f, -0.125f, -1.0f);
            s->f00 = 6;
            g->f5C = 0;
            return 0;
        }
    }
    if (s->f04 == 3) {
        UiSetWidgetAlpha_2907a0(g->f60, 0x51, 0.0f);
        UiSetTextString_28f510(g->f60, 0x51, MsgTableLookup_28aa30(D_00484A70, 0xA0), 0);
        memset(&b, 0, 0x34);
        b.f00 = ((s32)UiGetWidgetSprite_28fe10(g->f60, 0x51, 0));
        b.f04 = ((s32)UiGetWidgetText_28f620(g->f60, 0x51, 0));
        b.f10 = 0x1E;
        b.f14 = 0x13;
        b.f18 = 0xF;
        b.f1C = 0xB;
        UiWindowFitToText_28d0c0(&b, 0, 0, 0);
        UiFadeWidgetAlpha_290690(g->f60, 0x51, 1.0f, 0.125f, -1.0f);
        s->f00 = 1;
        s->f04 = -1;
        g->f5C = 1;
        return 0;
    }
    if (s->f00 == 0) {
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 6, 0, 1.0f);
        return 1;
    }
    return 0;
}
