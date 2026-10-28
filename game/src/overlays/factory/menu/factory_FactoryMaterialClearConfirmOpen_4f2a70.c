/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialClearConfirmOpen_4f2a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F2A70 -- open the parts sub-menu, once.
 *
 * ★ `sh $6, 0x14($2)` and the following `mult $2, $6, $4` share `$6`: retail
 * FORWARDS the value just stored into `rec->f14` rather than re-loading it, so
 * the multiply's left operand is the field, not a literal 1 -- the recorded
 * store-then-read shape.
 * ★ `o->f78 = 2;` written BEFORE `func_207DF0()` is what puts the `sb` in that
 * call's delay slot.
 */

typedef struct Rec {
    s16 f00;
    u8  pad02[0x2];
    s16 f04;
    s16 f06;
    s16 f08;
    u8  pad0A[0xA];
    s16 f14;
    u8  pad16[0x2];
    s16 f18;
} Rec;

typedef struct Page {
    u8    pad00[0x1E];
    u8    f1E;
    u8    pad1F[0x21];
    void *f40;
    void *f44;
    u8    pad48[0x30];
    u8    f78;
} Page;

extern void *D_004807EC;                        /* _gp - 0x4984 */

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

void factory_FactoryMaterialClearConfirmOpen_4f2a70(Page *o)
{
    Rec *row;
    Rec *rec;

    if (o->f78 == 0) {
        factory_FactoryMaterialClearConfirmLayout_4f2170((void *)o);
        UiSetWidgetVisible_290010(o->f40, 0x64, 0, -1);
        UiSetWidgetVisible_290010(o->f40, 0x63, 0, -1);
        UiSetWidgetVisible_290010(o->f40, 0x68, 0, -1);
        UiSetWidgetVisible_290010(o->f40, 0x6A, 1, -1);
        UiSetWidgetVisible_290010(D_004807EC, 0x97, 1, -1);
        UiFadeWidgetAlpha_290690(o->f40, 0x6A, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(D_004807EC, 0x97, 1.0f, 0.125f, -1.0f);
        row = ((Rec *)UiGetWidgetSprite_28fe10(o->f40, 0x75, 0));
        UiSetSpriteX_28fcd0(o->f40, 0x75, row->f00 + 2 + row->f18, 3);
        rec = ((Rec *)UiEntryListFindByTag_28ea40(o->f44, 0x893A));
        rec->f14 = 1;
        UiSetWidgetPos_290f60(D_004807EC, 0x97, rec->f04 + rec->f14 * rec->f08, rec->f06);
        o->f1E = 1;
        UiEntryListSelectByTag_28ea90(o->f44, 0x893A, 0);
        o->f78 = 2;
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
    }
}
