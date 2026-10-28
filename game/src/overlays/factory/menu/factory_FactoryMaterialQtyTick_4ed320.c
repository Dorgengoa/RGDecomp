/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialQtyTick_4ed320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx {
    u8    pad00[0x8];
    s16   f8;
    u8    padA[0x36];
    void *f40;
    void *f44;
    void *f48;
} Ctx;

typedef struct View {
    u8  pad00[0x8];
    s16 f8;
    u8  pad0A[0x6];
    s16 f10;
} View;

typedef struct Glyph {
    u8  pad00[0xC];
    s16 f0C;
} Glyph;

typedef struct Msg {
    s32   f0;
    u8    pad04[0x10];
    void *f14;
    s32   f18;
} Msg;

extern Ctx *D_00484A58;                         /* _gp - 0x718  */
extern f32  D_0047D35C;                         /* _gp - 0x7E14 */
extern f32  D_0047D4F8;                         /* _gp - 0x7C78 */
extern u8 D_004B2570[];

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

s32 factory_FactoryMaterialQtyTick_4ed320(s32 unused, s32 start)
{
    Glyph *g;
    View  *vw;
    Msg   *m;
    void  *h;
    s32    base;
    s32    v;
    s32    lim;
    s32    r;
    s32    n;

    if (start != 0) {
        UiEntryListSelectByTag_28ea90(D_00484A58->f44, 0x8930, 0);
        g = ((Glyph *)UiEntryListFindByTag_28ea40(D_00484A58->f44, 0x8930));
        factory_FactoryMaterialQtyPreset_4f2bf0(D_00484A58);
        g->f0C = factory_FactoryMaterialCellItemCount_4f3370(D_00484A58);
    }
    vw = ((View *)UiEntryListGetCurrentData_28ec60(D_00484A58->f44));
    base = vw->f10;
    r = MenuGridCursorInput_28e170(D_00484A58->f44, D_004B2570, 1, 0);
    v = vw->f10;
    if (v == base) {
        lim = vw->f8;
        if (PadIsTriggered_1839f0(D_004B2570, 0x1000) != 0) {
            v += 0xA;
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x4000) != 0) {
            v -= 0xA;
        }
        if (v < 0) {
            v = 0;
        } else if (lim < v) {
            v = lim;
        }
        vw->f10 = v;
    }
    if (v != base) {
        PlayMenuSe_289ef0(4);
        UiSetWidgetSubItemValue_291250(D_00484A58->f40, 0x79, 0, v);
    }
    if (r == 1) {
        n = UiGetWidgetSubItemValue_28ef00(D_00484A58->f40, 0x79, 0);
        if (n > 0) {
            PlayMenuSe_289ef0(5);
            UiSetWidgetColor_2905b0(D_00484A58->f40, 0x79, D_0047D35C, D_0047D35C, D_0047D35C,
                        -1.0f);
            UiFadeWidgetColor_2904e0(D_00484A58->f40, 0x79, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D4F8);
            D_00484A58->f8 = n;
            StateMachineSetState_28ede0(D_00484A58->f48, 0x89B2, 0);
            h = factory_FactoryMaterialGetCellItem_4f3290(D_00484A58);
            if (h != 0) {
                m = ((Msg *)FactoryGetRequestPtr_367ec0());
                m->f0 = 0xB;
                m->f14 = h;
                m->f18 = n;
            }
        } else {
            PlayMenuSe_289ef0(6);
        }
    } else if (r == 2) {
        PlayMenuSe_289ef0(6);
        D_00484A58->f8 = -1;
        StateMachineSetState_28ede0(D_00484A58->f48, 0x89B2, 0);
    }
    return 1;
}
