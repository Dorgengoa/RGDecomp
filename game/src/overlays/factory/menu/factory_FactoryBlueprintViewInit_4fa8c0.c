/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintViewInit_4fa8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FA8C0 -- build the whole crafting-result panel.
 *
 * 364 instructions, 12 conditional branches, 52 calls: the branch-light band.
 *
 * ★ `o->f80` is spelled out at every one of its ~40 call sites -- retail
 * reloads `lw $4, 0x80($19)` each time, and mwcc's per-basic-block CSE
 * reproduces that for free because a call separates every use.  `t` is the
 * opposite: `lw $16, 0x70($19)` happens ONCE and lives in a callee-saved
 * register for the rest of the function, so it is a named local.
 * ★ The tail dispatch is a `switch`, not an if/else-if chain: retail compares
 * 4, 3, 2, 1, 0 in that order and a compiled compare chain runs in REVERSE
 * source-case order.
 * ★ The 12/15 dispatch is NOT a switch -- the outer test is a `||` (source
 * order, because it short-circuits) and the inner one an if/else-if.  m2c
 * renders both as nested `switch`es.
 * ★ `beql $2, $0, .L004FACF4` on `e->f08 & 1` makes the SET case the
 * fall-through, so that is the `if` arm and the clear case is the `else`.
 * ★ `andi $5, $2, 0xFFFF` at every computed id says the id parameter is u16;
 * the constant ids need no mask, which is why only the loops carry one.
 */

typedef struct Sub {
    u8   pad00[0x4];
    s16  f04;
    u8   pad06[0x6];
    void *f0C;
} Sub;

typedef struct Elem {
    Sub  *f00;
    s16   f04;
    u8    pad06[0x2];
    u8    f08;
    u8    pad09[0x3];
    void *f0C;
} Elem;                                         /* 0x10 */

typedef struct Part {
    u8    pad00[0x10];
    void *f10;
    u8    pad14[0x18];
    s16   f2C;
} Part;

typedef struct Table {
    u8     pad00[0x2];
    s16    f02;
    Part  *f04;
    s16    f08;
    u8     pad0A[0x2];
    Elem  *f0C;
} Table;

typedef struct Panel {
    u8     pad00[0x70];
    Table *f70;
    u8     pad74[0xC];
    void  *f80;
    void  *f84;
} Panel;

extern void *D_004807EC;                        /* _gp - 0x4984 */
extern u8 factory_D_0050CCC8[];

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

void factory_FactoryBlueprintViewInit_4fa8c0(Panel *o)
{
    Table *t;
    Elem *e;
    s32 i;
    s16 k;

    factory_FactoryBlueprintListInit_4fbab0((void *)o);
    UiSetWidgetVisible_290010(o->f80, 0x27, 1, -1);
    UiSetWidgetVisible_290010(o->f80, 0x2A, 0, -1);
    UiSetWidgetVisible_290010(o->f80, 0x2B, 1, -1);
    UiSetWidgetVisible_290010(o->f80, 0x3A, 0, -1);
    UiSetWidgetsVisibleById_291110(D_004807EC, 0x97, 0, 1);
    UiEntryListSelectByTag_28ea90(o->f84, 0x894E, 1);
    UiSetSpriteSizeUvSize_28f670(o->f80, 0x3C, 0, 0, 0, 0, 0xC);
    UiSetSpriteSizeUvSize_28f670(o->f80, 0x3C, 0, 0, 0, 0, 0xD);
    UiSetSpriteSizeUvSize_28f670(o->f80, 0x3C, 0, 0, 0, 0, 0xE);
    UiSetWidgetVisible_290010(o->f80, 0x28, 0, -1);
    UiSetWidgetsVisibleById_291110(o->f80, 0x29, 0, 1);
    UiSetWidgetsVisibleById_291110(o->f80, 0x23, 0, 1);
    UiSetWidgetsVisibleById_291110(o->f80, 0x40, 0, 1);
    UiSetWidgetsVisibleById_291110(o->f80, 0x26, 0, 1);
    UiSetWidgetVisible_290010(o->f80, 0x3D, 0, -1);
    UiSetTextString_28f510(o->f80, 0x39, factory_D_0050CCC8, 2);
    UiSetTextString_28f510(o->f80, 0x39, factory_D_0050CCC8, 3);
    UiSetTextString_28f510(o->f80, 0x39, factory_D_0050CCC8, 5);
    t = o->f70;
    UiSetTextString_28f510(o->f80, 0x39, t->f04->f10, 4);
    UiSetWidgetVisible_290010(o->f80, 0x3E, 0, -1);
    UiSetWidgetVisible_290010(o->f80, 0x3F, 0, -1);
    UiSetSpriteFlags_290bd0(o->f80, 0x3E, (long long)(0x200), 0, 0, 0);
    UiSetSpriteFlags_290bd0(o->f80, 0x3F, (long long)(0x200), 0, 0, 0);

    k = t->f04->f2C;
    if (k == 0xC || k == 0xF) {
        if (k == 0xC) {
            UiSetSpriteSize_28fc30(o->f80, 0x3F, 0x28, 0x2D, 0);
            UiSetSpriteUvRect_28f9d0(o->f80, 0x3F, 0x140, 0x20, 0x20, 0x20, 0);
        } else if (k == 0xF) {
            UiSetSpriteSize_28fc30(o->f80, 0x3F, 0x28, 0x2D, 0);
            UiSetSpriteUvRect_28f9d0(o->f80, 0x3F, 0x140, 0, 0x20, 0x20, 0);
        }
        UiSetWidgetVisible_290010(o->f80, 0x3F, 1, -1);
    } else {
        UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(o->f80, 0x3E, 0), k, 0x28, 0x2D);
        UiSetWidgetVisible_290010(o->f80, 0x3E, 1, -1);
    }

    for (i = t->f08; i < 4; i++) {
        UiSetWidgetVisible_290010(o->f80, i + 0x31, 0, -1);
        UiSetSpriteSizeUvSize_28f670(o->f80, 0x3B, 0, 0, 0, 0, i);
    }

    e = t->f0C;
    for (i = 0; i < t->f08; i++, e++) {
        UiSetWidgetSubItemValue_291250(o->f80, i + 0x35, 0, i + 1);
        UiSetWidgetSubItemValue_291250(o->f80, i + 0x35, 1, e->f04);
        UiSetWidgetVisible_290010(o->f80, i + 0x31, 1, -1);
        UiSetSpriteSize_28fc30(o->f80, 0x3B, 0x16, 0x16, i);
        if (e->f08 & 1) {
            UiSetTextString_28f510(o->f80, i + 0x31, e->f00->f0C, 0);
            factory_FactoryBlueprintSetCategoryIcon_4f8e90(o, e->f00->f04, i);
        } else {
            UiSetTextString_28f510(o->f80, i + 0x31, e->f0C, 0);
            UiSetSpriteUvRect_28f9d0(o->f80, 0x3B, 0xA6, 0x2E, 0x16, 0x16, i);
        }
    }

    UiSetWidgetVisible_290010(o->f80, 0x2C, 0, -1);
    UiSetWidgetVisible_290010(o->f80, 0x2D, 0, -1);
    UiSetWidgetVisible_290010(o->f80, 0x2E, 0, -1);
    UiSetWidgetVisible_290010(o->f80, 0x2F, 0, -1);
    UiSetWidgetVisible_290010(o->f80, 0x30, 0, -1);
    switch (t->f02) {
    case 0:
        UiSetWidgetVisible_290010(o->f80, 0x2C, 1, -1);
        break;
    case 1:
        UiSetWidgetVisible_290010(o->f80, 0x2D, 1, -1);
        break;
    case 2:
        UiSetWidgetVisible_290010(o->f80, 0x2E, 1, -1);
        break;
    case 3:
        UiSetWidgetVisible_290010(o->f80, 0x2F, 1, -1);
        break;
    case 4:
        UiSetWidgetVisible_290010(o->f80, 0x30, 1, -1);
        break;
    }
}
