/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialLayout_4f3e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F3E00 -- build the two-choice confirm bar.
 *
 * ★ `bgez $2 / sra $3, $2, 1 / addiu $2, $2, 1 / sra $3, $2, 1` is the signed
 * `/ 2` bias sequence and nothing else -- m2c writes it out longhand, but a
 * plain division compiles to exactly these four instructions.
 */

typedef struct Page {
    u8    pad00[0x40];
    void *f40;
    u8    pad44[0x34];
    u8    f78;
} Page;

extern void *D_00484A70;                        /* _gp - 0x700 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMaterialLayout_4f3e00(Page *o)
{
    UiSetWidgetVisible_290010(o->f40, 0x68, 0, -1);
    UiSetSpriteFlags_290bd0(o->f40, 0x65, (long long)(0x200), 1, 0, 0);
    UiSetSpriteFlags_290bd0(o->f40, 0x65, (long long)(0x200), 1, 1, 0);
    UiSetTextString_28f510(o->f40, 0x65, MsgTableLookup_28aa30(D_00484A70, 0x18), 0);
    UiSetTextString_28f510(o->f40, 0x65, MsgTableLookup_28aa30(D_00484A70, 0xE6), 1);
    UiSetWidgetVisible_290010(o->f40, 0x69, 1, -1);
    UiSetWidgetAlpha_2907a0(o->f40, 0x69, 0.0f);
    UiSetSpriteFlags_290bd0(o->f40, 0x69, (long long)(0x200), 1, 0, 0);
    UiSetTextString_28f510(o->f40, 0x69, MsgTableLookup_28aa30(D_00484A70, 0xDC), 0);
    UiSetTextX_28f590(o->f40, 0x69, 0x100 - UiGetWidgetTextWidth_28f400(o->f40, 0x69, 0) / 2, 0);
    factory_FactoryMaterialClearConfirmLayout_4f2170(o);
    factory_FactoryMaterialReqListLayout_4f2d50(o);
    o->f78 = 0;
}
