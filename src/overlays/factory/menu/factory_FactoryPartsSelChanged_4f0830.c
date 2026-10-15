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

extern void  factory_FactoryPartsRefreshIcons_4efc80(Scr *o);
extern void  factory_FactoryPartsRefreshDetail_4efd30(Scr *o);
extern Item *func_28EA40(void *ctx, s32 id);
extern void  func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);

void factory_FactoryPartsSelChanged_4f0830(Scr *o)
{
    Item *it;
    Box  *b;

    it = func_28EA40(o->f90, 0x88F4);
    b = &it->b;
    if (o->f88 != 0) {
        return;
    }
    if (b->f12 != o->f60) {
        func_290F60(o->f8C, 0x44, 0, b->f12 * b->f6);
        factory_FactoryPartsRefreshDetail_4efd30(o);
        o->f60 = b->f12;
    }
    if (b->f16 != o->f62) {
        factory_FactoryPartsRefreshIcons_4efc80(o);
        factory_FactoryPartsRefreshDetail_4efd30(o);
        func_290F50(o->f8C, 0x43, 0x6F,
                    (s32)(32.0f + (f32)b->f16 * o->f6C), 0, 0.25f);
        o->f62 = b->f16;
    }
}
