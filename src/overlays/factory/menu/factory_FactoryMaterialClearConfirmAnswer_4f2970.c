#include "types.h"

typedef struct Job { s32 f00; } Job;

typedef struct Scr {
    u8    pad00[0x40];
    void *f40;
    void *f44;
    u8    pad48[0x30];
    u8    f78;
} Scr;

extern void *D_004807EC;

extern void func_28EA90(void *w, s32 id, s32 a);
extern void func_290010(void *w, s32 id, s32 a, s32 b);
extern void func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern Job *func_367EC0(void);

void factory_FactoryMaterialClearConfirmAnswer_4f2970(Scr *o, s32 v)
{
    Job *q;

    switch ((s8)v) {
    case 0:
        q = func_367EC0();
        q->f00 = 0xA;
        o->f78 = 3;
        func_28EA90(o->f44, 0x894E, 0);
        break;
    case 1:
        func_28EA90(o->f44, 0x891C, 0);
        o->f78 = 0;
        break;
    }
    func_290010(o->f40, 0x68, 1, -1);
    func_290010(o->f40, 0x64, 1, -1);
    func_290010(o->f40, 0x63, 1, -1);
    func_290690(o->f40, 0x6A, 0.0f, -0.125f, -1.0f);
    func_290690(D_004807EC, 0x97, 0.0f, -0.125f, -1.0f);
}
