/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintShowChosen_4f7ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F7AD0 -- re-caption the item panel.
 *
 * ★ `bnel $2, $0, L` with `lh $5, 0x78($16)` in the slot DUPLICATES the merge's
 * first instruction, so it is a plain forward branch: the guard is
 * `o->f70 == 0` and the tail runs on both paths.
 * ★ `D_0047D278` is INSIDE the gp window (0x47D170..0x48D170), so it stays a
 * plain extern and keeps its `%gp_rel` -- the overlay-data `const` rule is for
 * the `D_005xxxxx` addresses only.
 */

typedef struct Msg {
    u8  pad00[0xC];
    s32 f0C;
    u8  pad10[0x9C];
} Msg;                                          /* 0xAC */

typedef struct Item {
    u8   pad00[0x4];
    s16 *f04;
} Item;

typedef struct Page {
    u8    pad00[0x70];
    Item *f70;
    Item *f74;
    s16   f78;
    s16   f7A;
    u8    pad7C[0x4];
    void *f80;
} Page;

extern void *D_00484A70;                        /* _gp - 0x700  */
extern f32   D_0047D278;                        /* _gp - 0x7EF8 */
extern u8    factory_D_0050CCC8[];
extern u8    factory_D_0050FF10[];

/*rgp*/
/*rgp*/
extern void memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintShowChosen_4f7ad0(Page *o)
{
    Msg msg __attribute__((aligned(16)));

    MsgFormatParamsCtor_28aa00(&msg);
    memset(&msg, 0, 0xAC);
    msg.f0C = *o->f74->f04;
    memset(factory_D_0050FF10, 0, 0x40);
    MsgFormat_28a9a0(factory_D_0050FF10, MsgTableLookup_28aa30(D_00484A70, 0x23), &msg, 1);
    UiSetTextString_28f510(o->f80, 0x91, factory_D_0050CCC8, 0);
    UiSetTextString_28f510(o->f80, 0x91, factory_D_0050FF10, 0);
    if (o->f70 == 0) {
        UiSetWidgetVisible_290010(o->f80, 0x91, 1, -1);
        UiSetWidgetPos_290f60(o->f80, 0x91, 0x200, 0x191);
        UiMoveWidgetUniform_290f50(o->f80, 0x91, 0xBA, 0x191, D_0047D278, 0);
        UiFadeWidgetAlpha_290690(o->f80, 0x91, 1.0f, 0.125f, 0.0f);
        UiSetWidgetVisible_290010(o->f80, 0x29, 1, -1);
        UiSetWidgetPos_290f60(o->f80, 0x29, 0xEB, 0);
        UiMoveWidgetUniform_290f50(o->f80, 0x29, 0, 0, D_0047D278, 0);
        UiFadeWidgetAlpha_290690(o->f80, 0x29, 1.0f, 0.125f, 0.0f);
    }
    factory_FactoryBlueprintMarkCell_4f7a40(o, o->f78, o->f7A);
    o->f70 = o->f74;
}
