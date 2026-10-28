/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsSelect_4f02c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F02C0 -- open the recipe detail popup for the
 * item under the cursor.
 *
 * 264 instructions, 11 conditional branches, 41 calls: the branch-light band.
 *
 * ★ The failure block is written TWICE, not once behind a label: retail emits
 * two byte-identical copies of the `28EA90 / f88 = 2 / 004efa60 / three
 * 290690` sequence, and a shared `goto` would have emitted it once.  (The
 * copy-count rule, same as `004F62D0`'s inlined tail.)
 * ★ `n = 0; if (g != NULL) n = g->f06;` -- a NULL-or-value select is an `if`,
 * never a ternary; retail's `beqz` carries the zero in its delay slot.
 * ★ The float arguments are plain literals: 0x3F800000 / 0x3E000000 /
 * 0xBF800000 / 0xBE000000 are 1.0f, 0.125f, -1.0f, -0.125f materialised with
 * `lui` + `mtc1`, not gp loads, so they are NOT the named-constant class.
 */

typedef struct Meta {
    u8  pad00[0x16];
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} Meta;

typedef struct Item {
    s16   f00;
    u8    pad02[0xA];
    void *f0C;
} Item;

typedef struct Group {
    u8  pad00[0x6];
    s16 f06;
    u8  pad08[0x2];
    s16 f0A;
    s16 f0C;
} Group;

typedef struct Job {
    s32 f00;
    u8  pad04[0x4];
    s32 f08;
} Job;

typedef struct Iter {
    u8 pad00[0x8];
} Iter;

typedef struct Buf {
    s32 f00;
    u8  pad04[0xA8];
} Buf;                                          /* 0xAC */

typedef struct Panel {
    u8    pad00[0x64];
    s32   f64;
    s32   f68;
    u8    pad6C[0x8];
    u8    f74[0x14];
    u8    f88;
    u8    pad89[0x3];
    void *f8C;
    void *f90;
} Panel;

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8 factory_D_0050CAD8[];
extern u8 factory_D_0050FE90[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *p, s32 v, s32 n);
extern void strcat(void *p, void *s);
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

void factory_FactoryPartsSelect_4f02c0(Panel *o)
{
    Iter cur __attribute__((aligned(16)));
    Buf buf __attribute__((aligned(16)));
    Meta *m;
    Item *it;
    Group *g;
    Job *q;
    s32 h;
    s32 k;
    s32 n;
    s32 t;
    u8 v;

    v = o->f88;
    if (v == 2) {
        factory_FactoryPartsNoStockCloseMaybe_4f0100(o);
        return;
    }
    if (v != 0) {
        return;
    }
    m = UiEntryListFindByTag_28ea40(o->f90, 0x88F4);
    o->f64 = m->f16;
    o->f68 = m->f1A;
    IterInit_370170(&cur, o->f74, 0, 0);
    IterSeek_36fff0(&cur, m->f16 + m->f1A, 0, 0);
    it = IterGetCurrent_36ff80(&cur, 0, 0, 0);
    if (it == NULL) {
        return;
    }
    k = factory_FactoryPartsItemToGroup_4efb80(o, it->f00);
    h = GetFactoryObj_367f30();
    if (h == 0) {
        return;
    }
    g = ((Group *)factory_FactoryPartGroupFindById_504080(h, k));
    if ((g == NULL || g->f0A - g->f0C <= 0) && k != 0x12) {
        UiEntryListSelectByTag_28ea90(o->f90, 0x894E, 1);
        o->f88 = 2;
        factory_FactoryPartsShowNoStockMsgMaybe_4efa60(o, it->f00);
        UiFadeWidgetAlpha_290690(o->f8C, 0x46, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f8C, 0x42, 0.0f, -0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f8C, 0x4C, 0.0f, -0.125f, -1.0f);
        return;
    }
    if (k == 0x12 && factory_FactoryBeltHasRoom_500d30(h) == 0) {
        UiEntryListSelectByTag_28ea90(o->f90, 0x894E, 1);
        o->f88 = 2;
        factory_FactoryPartsShowNoStockMsgMaybe_4efa60(o, it->f00);
        UiFadeWidgetAlpha_290690(o->f8C, 0x46, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f8C, 0x42, 0.0f, -0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f8C, 0x4C, 0.0f, -0.125f, -1.0f);
        return;
    }
    UiFadeWidgetAlpha_290690(o->f8C, 0x42, 0.0f, -0.125f, -1.0f);
    UiFadeWidgetAlpha_290690(o->f8C, 0x4C, 0.0f, -0.125f, -1.0f);
    UiFadeWidgetAlpha_290690(o->f8C, 0x45, 1.0f, 0.125f, -1.0f);
    UiEntryListSelectByTag_28ea90(o->f90, 0x894E, 0);
    o->f88 = 1;
    k = factory_FactoryPartsItemToGroup_4efb80(o, it->f00);
    q = FactoryGetRequestPtr_367ec0();
    q->f00 = 5;
    q->f08 = k;
    memset(factory_D_0050FE90, 0, 0x20);
    UiSetTextString_28f510(o->f8C, 0x47, factory_D_0050CAD8, 0);
    UiSetTextString_28f510(o->f8C, 0x47, factory_D_0050CAD8, 1);
    g = ((Group *)factory_FactoryPartGroupFindById_504080(h, k));
    n = 0;
    if (g != NULL) {
        n = g->f06;
    }
    MsgFormatParamsCtor_28aa00(&buf);
    memset(&buf, 0, 0xAC);
    buf.f00 = n;
    MsgFormat_28a9a0(factory_D_0050FE90, MsgTableLookup_28aa30(D_00484A70, 0x1C), &buf, 1);
    t = factory_FactoryPartGroupToMsgId_4ef9f0(o, k);
    if (t > 0) {
        strcat(factory_D_0050FE90, MsgTableLookup_28aa30(D_00484A70, 0x78));
        strcat(factory_D_0050FE90, MsgTableLookup_28aa30(D_00484A70, t));
    }
    UiSetTextString_28f510(o->f8C, 0x47, it->f0C, 0);
    UiSetTextString_28f510(o->f8C, 0x47, factory_D_0050FE90, 1);
    UiFadeWidgetAlpha_290690(o->f8C, 0x47, 1.0f, 0.125f, -1.0f);
}
