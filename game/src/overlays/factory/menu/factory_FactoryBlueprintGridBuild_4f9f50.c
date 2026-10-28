/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintGridBuild_4f9f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F9F50 -- 2064 B / 516 words.  Full rebuild of the
 * recipe board: resets the 0x18 slots, lays out the first (highlighted) entry
 * with its 0x28 sub-panel, then the remaining entries, then counts the rest of
 * the list to size the scrollbar.
 *
 * DIVIDE-TRAP UNIT: four `/ 6` sites and seven `% 6` sites -> ELEVEN `div`
 * and FOUR `bnez / break 0,7` pairs.  `#pragma divbyzerocheck on` is the key
 * ([[NEGATIVES 6.6]]); without it the object is exactly eight words short.
 *
 * SEEDS: src/wf/factory/factory_FactoryBlueprintGridRefresh_4f9ac0.c (same iterator head, the same
 * `if (b0) ... if (b0 && b1)` shape, the same `f70->f00` tail) and
 * src/overlays/factory/factory_FactoryBlueprintOpenDetail_4f97a0.c.
 *
 * * The first list entry is SEPARATE SOURCE, not a peeled iteration -- it
 *   carries the func_28F510/28F400/28F590 group that the loop body lacks and
 *   spells its index as a literal 0.  `for (i = 1; ...)` is what puts
 *   `addiu $16,$0,1` in BOTH the taken and the fall-through path.
 * * The first entry's counter guard is `n / 6 > 0` (`blezl`), not `> k`; the
 *   two later copies are `> k` (`slt $1,$17,..`).  Same four lines, different
 *   constant -- the bodies are independently written.
 * * `sw $0,0x68($20)` in the call's delay slot is `o->f68 = 0.0f` immediately
 *   before the assignment of the call's result: mwcc cannot dead-store it
 *   because the callee could read the field.
 * * `e->f04` is re-read at every use (eight `lw 0x4($19)`), never named.
 */

#pragma divbyzerocheck on

typedef struct Card {
    u8    pad00[0xC];
    void *f0C;
    void *f10;
    u8    pad14[0x18];
    s16   f2C;
} Card;

typedef struct Ent {
    s16   f00;
    u8    pad02[0x2];
    Card *f04;
    u8    pad08[0xC];
    u8    b0 : 1;
    u8    b1 : 1;
} Ent;

typedef struct Rec {
    u8  pad00[0x12];
    s16 f12;
} Rec;

typedef struct Page {
    u8    pad00[0x68];
    f32   f68;
    u8    f6C;
    u8    pad6D[0x3];
    Ent  *f70;
    u8    pad74[0xC];
    void *f80;
    void *f84;
} Page;

typedef struct Iter { u8 pad[0x8]; } Iter;

typedef struct World {
    u8    pad00[0x8];
    void *f08;
} World;

typedef struct Zone {
    u8    pad00[0xA4];
    void *fA4;
} Zone;

typedef struct Area {
    u8  pad00[0xC];
    s32 f0C;
} Area;

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

void factory_FactoryBlueprintGridBuild_4f9f50(Page *o)
{
    Iter it __attribute__((aligned(16)));
    Rec *rec;
    Ent *e;
    s32  i;
    s32  n;
    s32  k;
    s32  c;
    s32  h;
    s32  key;

    key = ((Area *)((Zone *)((World *)GetGameData_1fede0())->f08)->fA4)->f0C;
    if (key != 0) {
        key = key + 0x88;
    }
    IterInit_370170(&it, key, 0, 0);
    UiSetWidgetVisible_290010(o->f80, 0x28, 0, -1);
    UiSetWidgetColor_2905b0(o->f80, 0x25, 0.0f, 0.0f, 0.0f, 1.0f);
    UiSetWidgetColor_2905b0(o->f80, 0x24, 0.0f, 0.0f, 0.0f, 1.0f);
    UiSetWidgetColor_2905b0(o->f80, 0x3E, 0.0f, 0.0f, 0.0f, 1.0f);
    UiSetWidgetColor_2905b0(o->f80, 0x3F, 0.0f, 0.0f, 0.0f, 1.0f);
    UiSetSpriteFlags_290bd0(o->f80, 0x25, (long long)(0), 0, 0, 0x18);
    UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(0), 0, 0, 2);
    UiSetSpriteSizeUvSize_28f670(o->f80, 0x24, 0, 0, 0, 0, 0);
    UiSetSpriteSizeUvSize_28f670(o->f80, 0x24, 0, 0, 0, 0, 1);
    UiSetWidgetsVisibleById_291110(o->f80, 0x23, 0, 1);
    for (i = 0; i < 0x18; i++) {
        UiSetSpriteSizeUvSize_28f670(o->f80, 0x22, 0x1A, 0x2A, 0x1A, 0x2A, i);
        UiSetSpriteSizeUvSize_28f670(o->f80, 0x25, 0, 0, 0, 0, i);
    }
    n = 0;
    k = 0;
    e = ((Ent *)IterNext_370040(&it));
    if (e != 0) {
        n++;
        if (e->b0 != 0) {
            UiSetWidgetVisible_290010(o->f80, 0x28, n, -1);
            UiSetTextString_28f510(o->f80, 0x28, e->f04->f10, 0);
            h = UiGetWidgetTextWidth_28f400(o->f80, 0x28, 0) / 2;
            c = 0xA4;
            c -= h;
            UiSetTextX_28f590(o->f80, 0x28, c + 0x27, 0);
            UiSetSpriteFlags_290bd0(o->f80, 0x25, (long long)(0x200), 0, 0, 0);
            if (e->f04->f2C == 12) {
                UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(0x200), 0, 0, 0);
            }
            if (e->f04->f2C == 15) {
                UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(0x200), 0, 1, 0);
            }
            factory_FactoryBlueprintGridSetIcon_4f8f90(o, e->f04, 0);
            UiSetSpriteSizeUvSize_28f670(o->f80, 0x22, 0, 0, 0, 0, 0);
            if (e->b0 != 0) {
                if (n / 6 > 0) {
                    k = n / 6;
                    if (n % 6 > 0) {
                        k = n / 6 + 1;
                    }
                } else if (n % 6 > 0) {
                    k = n / 6 + 1;
                }
            }
        }
        if (e->b0 != 0 && e->b1 != 0) {
            UiSetTextString_28f510(o->f80, 0x28, e->f04->f0C, 0);
            h = UiGetWidgetTextWidth_28f400(o->f80, 0x28, 0) / 2;
            c = 0xA4;
            c -= h;
            UiSetTextX_28f590(o->f80, 0x28, c + 0x27, 0);
            UiSetSpriteFlags_290bd0(o->f80, 0x25, (long long)(8), 0, 0, 0);
            if (e->f04->f2C == 12) {
                UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(8), 0, 0, 0);
            }
            if (e->f04->f2C == 15) {
                UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(8), 0, 1, 0);
                o->f6C = 1;
            }
        }
        if (o->f70 != 0 && e->f00 == o->f70->f00) {
            factory_FactoryBlueprintMarkCell_4f7a40(o, 0, 0);
        }
    }
    for (i = 1; i < 0x18 && e != 0; i++) {
        e = ((Ent *)IterNext_370040(&it));
        n++;
        if (e->b0 != 0) {
            UiSetSpriteFlags_290bd0(o->f80, 0x25, (long long)(0x200), 0, i, 0);
            if (e->f04->f2C == 12) {
                UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(0x200), 0, 0, 0);
            }
            if (e->f04->f2C == 15) {
                UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(0x200), 0, 1, 0);
            }
            factory_FactoryBlueprintGridSetIcon_4f8f90(o, e->f04, i);
            UiSetSpriteSizeUvSize_28f670(o->f80, 0x22, 0, 0, 0, 0, i);
            if (e->b0 != 0) {
                if (n / 6 > k) {
                    k = n / 6;
                    if (n % 6 > 0) {
                        k = n / 6 + 1;
                    }
                } else if (n % 6 > 0) {
                    k = n / 6 + 1;
                }
            }
        }
        if (e->b0 != 0 && e->b1 != 0) {
            UiSetSpriteFlags_290bd0(o->f80, 0x25, (long long)(8), 0, i, 0);
            if (e->f04->f2C == 12) {
                UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(8), 0, 0, 0);
            }
            if (e->f04->f2C == 15) {
                UiSetSpriteFlags_290bd0(o->f80, 0x24, (long long)(8), 0, 1, 0);
                o->f6C = 1;
            }
        }
        if (o->f70 != 0 && e->f00 == o->f70->f00) {
            factory_FactoryBlueprintMarkCell_4f7a40(o, (s16)(i % 6), (s16)(i / 6));
        }
    }
    while ((e = ((Ent *)IterNext_370040(&it))) != 0) {
        n++;
        if (e->b0 != 0) {
            if (n / 6 > k) {
                k = n / 6;
                if (n % 6 > 0) {
                    k = n / 6 + 1;
                }
            } else if (n % 6 > 0) {
                k = n / 6 + 1;
            }
            if (e->b1 != 0 && e->f04->f2C == 15) {
                o->f6C = 1;
            }
        }
    }
    o->f68 = 0.0f;
    o->f68 = UiPageScrollBarLayout_289710(o, 0x21, 0xEB, 4, k, 0);
    UiSetSpriteUv_28f970(o->f80, 0x21, 0x76, 0x56, 0);
    UiSetSpriteUv_28f970(o->f80, 0x21, 0x76, 0x5C, 1);
    UiSetSpriteUv_28f970(o->f80, 0x21, 0x76, 0x64, 2);
    UiSetWidgetPos_290f60(o->f80, 0x21, 0x170, 0x20);
    rec = ((Rec *)UiEntryListFindByTag_28ea40(o->f84, 0x88CC));
    rec->f12 = k - 1;
}
