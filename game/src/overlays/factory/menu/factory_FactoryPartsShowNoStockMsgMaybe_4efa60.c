/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsShowNoStockMsgMaybe_4efa60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EFA60 -- build one message box and show it.
 *
 * ★ Frame layout is the check here: the 0xAC record sits at 0x30($29) and the
 * 0x34 record at 0xE0($29), and mwcc allocates stack locals in REVERSE
 * declaration order, so the 0x34 one is declared FIRST.  Its declared SIZE is
 * the frame size -- pad both to the reference's own length.
 *
 * ★ `factory_D_0050CAD8` and `factory_D_0050FE10` are overlay data, outside the gp window
 * (0x47D170..0x48D170), so they must NOT take a %gp_rel relocation.  Spelled as
 * incomplete arrays they get `lui %hi` + `addiu %lo`, which is what retail has.
 *
 * ★ `msg.f0C = kind;` written BEFORE the clear of factory_D_0050FE10 is what puts the
 * `sw $16, 0x3C($29)` in that call's delay slot.
 */

typedef struct Box {
    s32 f00;
    s32 f04;
    u8  pad08[0x8];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x14];
} Box;                                          /* 0x34 */

typedef struct Msg {
    u8  pad00[0xC];
    s32 f0C;
    u8  pad10[0x9C];
} Msg;                                          /* 0xAC */

typedef struct Page {
    u8    pad0[0x8C];
    void *f8C;
} Page;

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    factory_D_0050CAD8[];
extern u8    factory_D_0050FE10[];

extern void memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryPartsShowNoStockMsgMaybe_4efa60(Page *o, s32 kind)
{
    Box box __attribute__((aligned(16)));
    Msg msg __attribute__((aligned(16)));

    memset(&box, 0, 0x34);
    box.f00 = ((s32)UiGetWidgetSprite_28fe10(o->f8C, 0x46, 0));
    box.f04 = ((s32)UiGetWidgetText_28f620(o->f8C, 0x46, 0));
    MsgFormatParamsCtor_28aa00(&msg);
    memset(&msg, 0, 0xAC);
    UiSetTextString_28f510(o->f8C, 0x46, factory_D_0050CAD8, 0);
    msg.f0C = kind;
    memset(factory_D_0050FE10, 0, 0x80);
    MsgFormat_28a9a0(factory_D_0050FE10, MsgTableLookup_28aa30(D_00484A70, 0x82), &msg, 1);
    UiSetTextString_28f510(o->f8C, 0x46, factory_D_0050FE10, 0);
    box.f10 = 0x1E;
    box.f14 = 0x13;
    box.f18 = 0xF;
    box.f1C = 0xB;
    UiWindowFitToText_28d0c0(&box, 0, 0, 0);
}
