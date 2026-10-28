/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuRowHighlight_4f0c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Pair {
    s32 f0;
    s32 f4;
} Pair;

typedef struct Sub {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} Sub;

typedef struct Hdr {
    u8  pad00[0x4];
    Sub f04;
} Hdr;

typedef struct Ent {
    s16 f00;
    u8  pad02[0x12];
    s16 f14;
    u8  pad16[0x2];
    s16 f18;
} Ent;

typedef struct Scr {
    u8    pad00[0x64];
    void *f64;
    void *f68;
    u8    pad6C[0x8];
    s32   f74;
    u8    f78;
} Scr;

extern Pair factory_D_0050BCE0[];
extern Pair factory_D_0050BD20[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMenuRowHighlight_4f0c80(Scr *o)
{
    Pair  a[8] __attribute__((aligned(16)));
    Pair  b[8] __attribute__((aligned(16)));
    Pair *s;
    Pair *d;
    Hdr  *h;
    Sub  *m;
    Ent  *e;
    s32   i;

    switch (o->f78) {
    case 0:
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f68, 0x88B8));
        m = &h->f04;
        UiSetSpriteSizeUvSize_28f670(o->f64, 0x18, 0x20, 0x20, 0x20, 0x20, o->f74);
        UiSetSpriteSizeUvSize_28f670(o->f64, 0x18, 0, 0, 0, 0, m->f12);
        s = factory_D_0050BCE0;
        d = a;
        for (i = 8; i > 0; i--, s++, d++) {
            d->f0 = s->f0;
            d->f4 = s->f4;
        }
        UiSetSpriteUv_28f970(o->f64, 0x19, a[m->f12].f0, a[m->f12].f4, 0);
        s = factory_D_0050BD20;
        d = b;
        for (i = 8; i > 0; i--, s++, d++) {
            d->f0 = s->f0;
            d->f4 = s->f4;
        }
        UiSetSpritePos_28fd10(o->f64, 0x19, b[m->f12].f0, b[m->f12].f4, 0);
        UiMoveWidgetUniform_290f50(o->f64, m->f12 + 4, 0xF, 0, 0.5f, 0);
        UiMoveWidgetUniform_290f50(o->f64, o->f74 + 4, 0, 0, 0.5f, 0);
        UiSetSpriteSizeUvSize_28f670(o->f64, o->f74 + 4, 0x73, 0x1E, 4, 4, 3);
        UiSetSpriteSizeUvSize_28f670(o->f64, o->f74 + 4, 0, 0, 0, 0, 4);
        UiSetSpriteSizeUvSize_28f670(o->f64, m->f12 + 4, 0, 0, 0, 0, 3);
        UiSetSpriteSizeUvSize_28f670(o->f64, m->f12 + 4, 0x73, 0x1E, 0x4C, 0x18, 4);
        o->f74 = m->f12;
        break;
    case 1:
        if (((Hdr *)UiEntryListFindByTag_28ea40(o->f68, 0x88C2))->f04.f10 == 0) {
            e = ((Ent *)UiGetWidgetSprite_28fe10(o->f64, 0x1D, 0));
            UiSetSpriteX_28fcd0(o->f64, 0x1D, e->f00 + 2, 3);
        } else {
            e = ((Ent *)UiGetWidgetSprite_28fe10(o->f64, 0x1D, 0));
            UiSetSpriteX_28fcd0(o->f64, 0x1D, e->f00 + 2 + e->f18, 3);
        }
        break;
    }
}
