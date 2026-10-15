#include "types.h"

/* factory.bin overlay, 0x004EFA60 -- build one message box and show it.
 *
 * ★ Frame layout is the check here: the 0xAC record sits at 0x30($29) and the
 * 0x34 record at 0xE0($29), and mwcc allocates stack locals in REVERSE
 * declaration order, so the 0x34 one is declared FIRST.  Its declared SIZE is
 * the frame size -- pad both to the reference's own length.
 *
 * ★ `D_0050CAD8` and `D_0050FE10` are overlay data, outside the gp window
 * (0x47D170..0x48D170), so they must NOT take a %gp_rel relocation.  Spelled as
 * incomplete arrays they get `lui %hi` + `addiu %lo`, which is what retail has.
 *
 * ★ `msg.f0C = kind;` written BEFORE the clear of D_0050FE10 is what puts the
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
extern u8    D_0050CAD8[];
extern u8    D_0050FE10[];

extern void func_131B60(void *p, s32 v, s32 n);
extern s32  func_28FE10(void *w, s32 id, s32 a);
extern s32  func_28F620(void *w, s32 id, s32 a);
extern void func_28AA00(void *p);
extern void func_28F510(void *w, s32 id, void *p, s32 a);
extern s32  func_28AA30(void *ctx, s32 id);
extern void func_28A9A0(void *p, s32 a, void *src, s32 n);
extern void func_28D0C0(void *p, s32 a, s32 b, s32 c);

void factory_FactoryPartsShowNoStockMsgMaybe_4efa60(Page *o, s32 kind)
{
    Box box;
    Msg msg;

    func_131B60(&box, 0, 0x34);
    box.f00 = func_28FE10(o->f8C, 0x46, 0);
    box.f04 = func_28F620(o->f8C, 0x46, 0);
    func_28AA00(&msg);
    func_131B60(&msg, 0, 0xAC);
    func_28F510(o->f8C, 0x46, D_0050CAD8, 0);
    msg.f0C = kind;
    func_131B60(D_0050FE10, 0, 0x80);
    func_28A9A0(D_0050FE10, func_28AA30(D_00484A70, 0x82), &msg, 1);
    func_28F510(o->f8C, 0x46, D_0050FE10, 0);
    box.f10 = 0x1E;
    box.f14 = 0x13;
    box.f18 = 0xF;
    box.f1C = 0xB;
    func_28D0C0(&box, 0, 0, 0);
}
