/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintShowRecipe_4f9380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F9380 -- refresh the result panel for a new table.
 *
 * ★★ A NEAR-TWIN OF factory_FUN_004FA8C0, and that is what made it cheap: the
 * same three loops and the same two dispatches, with `t` arriving as the
 * SECOND PARAMETER instead of being loaded from `o->f70`, no opening block of
 * setup calls, and `o->f74 = t;` at the end.  The twin's structure decisions
 * -- the `||` rather than a switch at 12/15, the REVERSED compare chain of the
 * tail switch, the u16 id parameter, `o->f80` spelled out at every call --
 * all transfer unchanged.
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
    Table *f74;
    u8     pad78[0x8];
    void  *f80;
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

void factory_FactoryBlueprintShowRecipe_4f9380(Panel *o, Table *t)
{
    Elem *e;
    s32 i;
    s16 k;

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
    o->f74 = t;
}
