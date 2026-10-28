/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuBuildWidgets_4ea1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EA1D0 -- build the factory screen's widgets.
 *
 * 240 instructions, ZERO conditional branches, 50 calls: a straight-line
 * construction list, which is why it is early in the factory grind.
 *
 * ★ THE GLOBALS ARE SPELLED AT EVERY USE, NOT HOISTED.  Retail re-loads
 * `lw $4, -0x498C($28)` before each of the five uses in a block.  A static
 * inline helper taking `Item *w` would have parked the pointer in a
 * callee-saved register across the calls, so the five blocks are the source's
 * own repetition and not a helper.  Every use here is separated by a call, so
 * mwcc's per-basic-block CSE re-reads the global by itself.
 *
 * ★ `lhu 0xA / dsll32 16 / dsrl32 18` is a 14-BIT BITFIELD, measured in a probe
 * TU against six other spellings: `(v >> 2) & 0x3FFF` gives sra+andi, `v >> 2`
 * gives sra, and only `u16 :2` followed by `u16 f:14` gives the double shift.
 * mwcc allocates u16 bitfields from the LSB, so the 2-bit filler is declared
 * FIRST.
 *
 * ⚠ func_42C950 takes TWO arguments.  m2c gives it four because $6 still holds
 * the byte read back for the flag insert and $7 still holds the frame pointer;
 * neither is marshalled for the call.  Only $4 and $5 are written for it.
 *
 * ⚠ The float argument ORDER at func_2905B0 is unconstrained by the listing --
 * this ABI numbers float and integer arguments independently, so nothing in the
 * reference distinguishes the three zeroes from each other.
 */

typedef struct Rec {
    u8   pad0[4];
    s32  f4;
    u8   pad8[2];
    __extension__ unsigned short  fA_fill : 2;
    unsigned short  fA : 14;
} __attribute__((aligned(2))) Rec;

typedef struct Item {
    u8   pad0[8];
    s32  f8;
} Item;

typedef struct Frame {
    u8    pad0[0x18];
    void *f18;
    u8    pad1C[4];
    u8    f20_b0 : 1;
    u8    f20_rest : 7;
    u8    f21;
} Frame;

typedef struct Slot {
    s16 f0;
    u8  pad2[2];
    s32 f4;
    s32 f8;
} Slot;

extern void *D_004807E4;        /* the four label items, 0x2A..0x2D */
extern void *D_004807E8;
extern void *D_004807EC;
extern void *D_004807F0;
extern void *D_004807F4;        /* the frame, 0x1F */
extern void *D_004807F8;        /* the shared slot */
extern void *D_00484A28;
extern void *D_00484A2C;
extern void *D_00484A44;
extern void *D_00484A48;
extern void *D_00484A4C;
extern void *D_00484A50;
extern void *D_00484A54;
extern void *D_00484A58;
extern void *D_00484A5C;
extern void *D_00484A60;
extern f32   D_0047DD80;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMenuBuildWidgets_4ea1d0(void)
{
    void *ctx;
    Rec *r;
    s32 a;
    s32 b;
    Frame *f;
    s32 h;
    Slot *s;

    ctx = GetMenuResGroup_206a40();

    r = ((Rec *)ResGroupListFindById_42c500(ctx, 0x2A));
    a = r->f4;
    b = r->fA;
    UiWidgetListReset_2912e0(D_004807E4);
    UiInitWidgetPool_290390(D_004807E4, D_00484A2C, b);
    UiAddWidgets_2901d0(D_004807E4, a, 0);
    ((Item *)D_004807E4)->f8 = 0x32B;
    UiTextStyleReset_290450();

    r = ((Rec *)ResGroupListFindById_42c500(ctx, 0x2B));
    a = r->f4;
    b = r->fA;
    UiWidgetListReset_2912e0(D_004807E8);
    UiInitWidgetPool_290390(D_004807E8, D_00484A2C, b);
    UiAddWidgets_2901d0(D_004807E8, a, 0);
    ((Item *)D_004807E8)->f8 = 0x32D;
    UiTextStyleReset_290450();

    r = ((Rec *)ResGroupListFindById_42c500(ctx, 0x2C));
    a = r->f4;
    b = r->fA;
    UiWidgetListReset_2912e0(D_004807EC);
    UiInitWidgetPool_290390(D_004807EC, D_00484A2C, b);
    UiAddWidgets_2901d0(D_004807EC, a, 0);
    ((Item *)D_004807EC)->f8 = 0x32D;
    UiTextStyleReset_290450();

    r = ((Rec *)ResGroupListFindById_42c500(ctx, 0x2D));
    a = r->f4;
    b = r->fA;
    UiWidgetListReset_2912e0(D_004807F0);
    UiInitWidgetPool_290390(D_004807F0, D_00484A2C, b);
    UiAddWidgets_2901d0(D_004807F0, a, 0);
    ((Item *)D_004807F0)->f8 = 0x32D;
    UiTextStyleReset_290450();

    r = ((Rec *)ResGroupListFindById_42c040(ctx, 0x1F));
    a = r->f4;
    b = r->fA;
    UiEntryListReset_28ec80(D_004807F4);
    UiEntryListAlloc_28e0c0(D_004807F4, D_00484A2C, b);
    UiEntryListLoad_28eb70(D_004807F4, a, D_004807E4);

    f = (Frame *)D_004807F4;
    f->f18 = D_00484A28;
    f->f20_b0 = 0;
    f->f21 = 0;
    h = MenuStateTableForId_42c950(ctx, 0x1F);

    s = (Slot *)D_004807F8;
    s->f4 = 0;
    s->f8 = 0;
    s->f0 = 0;
    ((Slot *)D_004807F8)->f8 = h;

    factory_FactoryMenuClearRefs_4f1210(D_00484A44);
    factory_FactoryMenuSetRefs_4f11f0(D_00484A44, D_004807E4, D_004807F4, D_004807F8, D_00484A2C);
    factory_FactoryBlueprintClearRefs_4fbe00(D_00484A48);
    factory_FactoryBlueprintSetRefs_4fbdd0(D_00484A48, D_004807E4, D_004807F4, D_004807F8, D_00484A2C);
    factory_FactoryPartsClearRefs_4f0c70(D_00484A4C);
    factory_FactoryPartsSetRefs_4f0c50(D_00484A4C, D_004807E4, D_004807F4, D_004807F8, D_00484A2C);
    factory_FactoryMoveClearRefs_4f47c0(D_00484A50);
    factory_FactoryMoveSetRefs_4f47a0(D_00484A50, D_004807E4, D_004807F4, D_004807F8, D_00484A2C);
    factory_FactoryRemoveClearRefs_4fd100(D_00484A54);
    factory_FactoryRemoveSetRefs_4fd0e0(D_00484A54, D_004807E4, D_004807F4, D_004807F8, D_00484A2C);
    factory_FactoryMaterialClearRefs_4f3fc0(D_00484A58);
    factory_FactoryMaterialSetRefs_4f3f60(D_00484A58, D_004807E4, D_004807F4, D_004807F8, D_00484A2C);
    factory_FactoryHelpClearRefs_4f2150(D_00484A5C);
    factory_FactoryHelpSetRefs_4f2100(D_00484A5C, D_004807E4, D_004807F4, D_004807F8, D_00484A2C);
    factory_FactoryProduceClearRefs_4f7a20(D_00484A60);
    factory_FactoryProduceSetRefs_4f7980(D_00484A60, D_004807E4, D_004807F4, D_004807F8, D_00484A2C);

    UiPageSetLayout_289c30(D_00484A48, D_004807E4);
    UiPageSetLayout_289c30(D_00484A4C, D_004807E4);
    UiPageSetLayout_289c30(D_00484A5C, D_004807E4);

    UiSetWidgetVisible_290010(D_004807E4, 1, 1, -1);
    UiSetWidgetVisible_290010(D_004807E4, 0xC, 0, -1);
    UiSetWidgetColor_2905b0(D_004807E4, 2, 0.0f, 0.0f, 0.0f, D_0047DD80);
    UiSetWidgetVisible_290010(D_004807E4, 0x1A, 0, -1);
    UiSetWidgetAlpha_2907a0(D_004807E4, 0x1A, 0.0f);
}
