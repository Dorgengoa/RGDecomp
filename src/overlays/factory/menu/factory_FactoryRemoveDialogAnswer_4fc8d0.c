#include "types.h"

typedef struct Unit {
    u8    pad00[0x64];
    u8    f64;
    u8    f65;
    u8    pad66[0x2];
    void *f68;
    void *f6C;
} Unit;

typedef struct Msg {
    s32 f0;
} Msg;

extern void *D_004807EC;                        /* _gp - 0x4984 */

extern Msg *func_367EC0(void);
extern void func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void func_28EA90(void *w, s32 id, s32 a);
extern void factory_FactoryRemoveDialogLayout_4fbe10(Unit *u);

void factory_FactoryRemoveDialogAnswer_4fc8d0(Unit *u, s32 sel)
{
    Msg *m;
    u8   ok;

    if (u->f64 == 1) {
        ok = 1;
    } else if (u->f64 == 2) {
        ok = 1;
    } else if (u->f64 == 3) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (!ok) {
        return;
    }
    u->f65 = 1;
    m = func_367EC0();
    switch ((s8)sel) {
    case 1:
        func_290690(u->f68, 0x5A, 0.0f, -0.125f, -1.0f);
        func_290690(u->f68, 0x55, 1.0f, 0.125f, -1.0f);
        u->f64 = 2;
        factory_FactoryRemoveDialogLayout_4fbe10(u);
        break;
    case 2:
        func_290690(u->f68, 0x5A, 0.0f, -0.125f, -1.0f);
        func_290690(u->f68, 0x55, 1.0f, 0.125f, -1.0f);
        u->f64 = 3;
        factory_FactoryRemoveDialogLayout_4fbe10(u);
        break;
    case 3:
        func_290690(u->f68, 0x55, 0.0f, -0.125f, -1.0f);
        func_290690(D_004807EC, 0x97, 0.0f, -0.125f, -1.0f);
        u->f64 = 0;
        m->f0 = 8;
        break;
    case 4:
        func_290690(u->f68, 0x55, 0.0f, -0.125f, -1.0f);
        func_290690(D_004807EC, 0x97, 0.0f, -0.125f, -1.0f);
        u->f64 = 0;
        m->f0 = 9;
        break;
    case -1:
        func_290690(u->f68, 0x5A, 0.0f, -0.125f, -1.0f);
        func_290690(u->f68, 0x55, 0.0f, -0.125f, -1.0f);
        func_290690(D_004807EC, 0x97, 0.0f, -0.125f, -1.0f);
        func_28EA90(u->f6C, 0x8908, 0);
        u->f64 = 0;
        m->f0 = 7;
        break;
    }
}
