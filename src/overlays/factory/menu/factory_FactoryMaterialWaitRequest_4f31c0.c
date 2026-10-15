#include "types.h"

typedef struct Job { s32 f00; } Job;

typedef struct Scr {
    u8    pad00[0x40];
    void *f40;
    void *f44;
    u8    pad48[0x30];
    u8    f78;
} Scr;

extern void  factory_FactoryMaterialMarkFilledRows_4f25c0(Scr *o);
extern void  func_28EA90(void *w, s32 id, s32 a);
extern void  func_1B9520(void *p, s32 a, s32 b, f32 t);
extern void *func_207DF0(void);
extern void  func_2907A0(void *w, s32 id, f32 t);
extern Job  *func_367EC0(void);

s32 factory_FactoryMaterialWaitRequest_4f31c0(Scr *o)
{
    u8 v;

    v = o->f78;
    if (v != 1 && v != 3) {
        return 1;
    }
    if (func_367EC0()->f00 == 0) {
        if (o->f78 == 1) {
            func_2907A0(o->f40, 0xB0, 1.0f);
            func_2907A0(o->f40, 0x69, 0.0f);
        }
        o->f78 = 0;
        func_28EA90(o->f44, 0x891C, 0);
        factory_FactoryMaterialMarkFilledRows_4f25c0(o);
        func_1B9520(func_207DF0(), 6, 0, 1.0f);
    }
    return 0;
}
