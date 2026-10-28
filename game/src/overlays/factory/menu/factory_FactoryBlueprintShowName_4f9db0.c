/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintShowName_4f9db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Iter { u8 pad00[0x8]; } Iter;

typedef struct Res {
    u8    pad00[0xC];
    void *f0C;
    void *f10;
} Res;

typedef struct Node {
    u8    pad00[0x4];
    Res  *f04;
    u8    pad08[0xC];
    u8    b0 : 1;
    u8    b1 : 1;
    u8    pad14 : 6;
} Node;

typedef struct Hdr {
    u8  pad00[0x14];
    s16 f14;
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} Hdr;

typedef struct Blk {
    u8    pad00[0xC];
    u8   *f0C;
} Blk;

typedef struct Slot {
    u8    pad00[0xA4];
    Blk  *fA4;
} Slot;

typedef struct Ctx {
    u8    pad00[0x8];
    Slot *f08;
} Ctx;

typedef struct Scr {
    u8    pad00[0x80];
    void *f80;
    void *f84;
} Scr;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintShowName_4f9db0(Scr *o)
{
    Iter  it __attribute__((aligned(16)));
    Hdr  *h;
    Node *n;
    u8   *q;
    s32   v;
    s32   k;

    UiSetWidgetVisible_290010(o->f80, 0x28, 0, -1);
    q = ((Ctx *)GetGameData_1fede0())->f08->fA4->f0C;
    if (q != 0) {
        q = q + 0x88;
    }
    IterInit_370170(&it, q, 0, 0);
    h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f84, 0x88CC));
    IterSeek_36fff0(&it, h->f14 + (h->f16 + h->f1A) * 6, 0, 0);
    n = ((Node *)IterGetCurrent_36ff80(&it, 0, 0, 0));
    if (n != 0) {
        if (n->b0) {
            UiSetWidgetVisible_290010(o->f80, 0x28, 1, -1);
            UiSetTextString_28f510(o->f80, 0x28, n->f04->f10, 0);
            v = UiGetWidgetTextWidth_28f400(o->f80, 0x28, 0);
            k = 0xA4 - v / 2;
            UiSetTextX_28f590(o->f80, 0x28, k + 0x27, 0);
        }
        if (n->b0 && n->b1) {
            UiSetTextString_28f510(o->f80, 0x28, n->f04->f0C, 0);
            v = UiGetWidgetTextWidth_28f400(o->f80, 0x28, 0);
            k = 0xA4 - v / 2;
            UiSetTextX_28f590(o->f80, 0x28, k + 0x27, 0);
        }
    }
}
