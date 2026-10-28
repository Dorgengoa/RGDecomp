/* rgp:protos */
#define RGP_SELF_factory_FactoryMoveOpen_4f45a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F45A0 -- open the blueprint confirm prompt.  508
 * bytes, 128 instructions, 3 conditional branches, 22 calls (br/ins 0.023):
 * the branch-light band, and close to straight transcription.
 *
 * ★ The LAST struct store (`sty.f1C = 0xB`) fills func_28D0C0's delay slot and
 * `o->f5C = 0;` follows the call -- writing it before the call instead swaps
 * those two words, at the right length.
 *
 * D_00484A70 is _gp - 0x700 and stays plain.
 */

typedef struct Sty {
    s32 f00;
    s32 f04;
    u8  pad08[0x8];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x14];
} Sty;                                          /* 0x34 */

typedef struct Game { u8 pad000[0x2D0]; s32 f2D0; } Game;
typedef struct Job  { s32 f00; } Job;

typedef struct Panel {
    u8    pad00[0x5C];
    u8    f5C;
    u8    pad5D[0x3];
    void *f60;
    u8    pad64[0xC];
    u8    f70;
} Panel;

extern void *D_00484A70;                        /* _gp - 0x700 */

extern void  memset(void *p, s32 v, s32 n);
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

void factory_FactoryMoveOpen_4f45a0(Panel *o)
{
    Sty   sty __attribute__((aligned(16)));
    Game *h;
    Job  *job;

    UiSetSpriteFlags_290bd0(o->f60, 0x4E, (long long)(0x200), 1, 0, 0);
    UiSetTextString_28f510(o->f60, 0x4E, MsgTableLookup_28aa30(D_00484A70, 0x18), 0);
    UiSetTextString_28f510(o->f60, 0x4E, MsgTableLookup_28aa30(D_00484A70, 8), 1);
    UiSetTextString_28f510(o->f60, 0x4E, MsgTableLookup_28aa30(D_00484A70, 6), 2);
    UiSetTextString_28f510(o->f60, 0x4E, MsgTableLookup_28aa30(D_00484A70, 7), 3);
    h = ((Game *)GetFactoryObj_367f30());
    if (h == 0) {
        return;
    }
    job = ((Job *)FactoryGetRequestPtr_367ec0());
    if (job == 0) {
        return;
    }
    job->f00 = 6;
    h->f2D0 = h->f2D0 & ~1;
    UiSetWidgetVisible_290010(o->f60, 0x4F, 1, -1);
    UiSetWidgetAlpha_2907a0(o->f60, 0x4F, 0.0f);
    if (o->f70 == 0) {
        UiSetWidgetVisible_290010(o->f60, 0x4E, 1, -1);
    } else {
        UiSetWidgetVisible_290010(o->f60, 0x4E, 0, -1);
    }
    UiSetWidgetAlpha_2907a0(o->f60, 0x51, 0.0f);
    UiSetTextString_28f510(o->f60, 0x51, MsgTableLookup_28aa30(D_00484A70, 0xA0), 0);
    memset(&sty, 0, 0x34);
    sty.f00 = ((s32)UiGetWidgetSprite_28fe10(o->f60, 0x51, 0));
    sty.f04 = ((s32)UiGetWidgetText_28f620(o->f60, 0x51, 0));
    sty.f10 = 0x1E;
    sty.f14 = 0x13;
    sty.f18 = 0xF;
    sty.f1C = 0xB;
    UiWindowFitToText_28d0c0(&sty, 0, 0, 0);
    o->f5C = 0;
}
