/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsSelChanged_4f0830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Box {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    u8  pad8[8];
    s16 f10;
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Box;

typedef struct Item {
    u8  pad0[4];
    Box b;
} Item;

typedef struct Scr {
    u8    pad00[0x60];
    s16   f60;
    s16   f62;
    u8    pad64[8];
    f32   f6C;
    u8    pad70[0x18];
    u8    f88;
    u8    pad89[3];
    void *f8C;
    void *f90;
} Scr;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryPartsSelChanged_4f0830(Scr *o)
{
    Item *it;
    Box  *b;

    it = ((Item *)UiEntryListFindByTag_28ea40(o->f90, 0x88F4));
    b = &it->b;
    if (o->f88 != 0) {
        return;
    }
    if (b->f12 != o->f60) {
        UiSetWidgetPos_290f60(o->f8C, 0x44, 0, b->f12 * b->f6);
        factory_FactoryPartsRefreshDetail_4efd30(o, 0, 0, 0);
        o->f60 = b->f12;
    }
    if (b->f16 != o->f62) {
        factory_FactoryPartsRefreshIcons_4efc80(o, 0, 0, 0);
        factory_FactoryPartsRefreshDetail_4efd30(o, 0, 0, 0);
        UiMoveWidgetUniform_290f50(o->f8C, 0x43, 0x6F, (s32)(32.0f + (f32)b->f16 * o->f6C), 0.25f, 0
);
        o->f62 = b->f16;
    }
}
