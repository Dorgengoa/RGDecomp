#include "types.h"

typedef struct Scr {
    u8    pad00[0x88];
    u8    f88;
    u8    pad89[0x3];
    void *f8C;
    void *f90;
} Scr;

extern void func_28EA90(void *w, s32 id, s32 a);
extern void func_290690(void *w, s32 id, f32 a, f32 b, f32 c);

void factory_FactoryPartsNoStockCloseMaybe_4f0100(Scr *o)
{
    o->f88 = 0;
    func_28EA90(o->f90, 0x88F4, 0);
    func_290690(o->f8C, 0x46, 0.0f, -0.125f, -1.0f);
    func_290690(o->f8C, 0x42, 1.0f, 0.125f, -1.0f);
    func_290690(o->f8C, 0x4C, 1.0f, 0.125f, -1.0f);
}
