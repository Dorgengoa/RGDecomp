#include "types.h"

extern "C" void UnitCtorReset_3b8a80(void *);
extern "C" u8 D_00471FE0[0x40];
extern "C" u8 D_00472050[0x40];
extern "C" u8 D_00472170[0x40];
extern "C" u8 D_00472250[0x40];
extern "C" u8 D_00474100[0x400];
extern "C" u8 D_00474440[0x400];
extern "C" u8 D_004746A0[0x400];
extern "C" u8 D_00474F80[0x400];
extern "C" u8 D_004752BC[0x40];
extern "C" u8 D_004753E0[0x400];
extern "C" u8 D_0047571C[0x40];

struct Obj {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
};

typedef struct {
    void *unk0;
    u8 pad4[0xc4];
    s64 unkC8;
    u8 padD0[0xd8];
    s64 unk1A8;
    u8 pad1B0[0x8];
    s64 unk1B8;
    u8 pad1C0[0x70];
    void *unk230;
} T3bbd20_arg0;

extern "C" void *UnitCtor_3bbd20(T3bbd20_arg0 *arg0)
{
    u8 *var_16;

    arg0->unk0 = D_00471FE0;
    arg0->unk0 = D_00474440;
    UnitCtorReset_3b8a80(arg0);
    arg0->unk0 = D_00474100;
    arg0->unkC8 = 0;
    arg0->unk1A8 = 0;
    arg0->unk1B8 = 0;
    arg0->unk230 = D_00472250;
    arg0->unk230 = D_004746A0;
    arg0->unk0 = D_004753E0;
    var_16 = (u8 *)arg0 + 0x278;
    arg0->unk230 = D_0047571C;
    do {
        *(void **)var_16 = D_00471FE0;
        *(void **)var_16 = D_00472170;
        ((Obj *)var_16)->f5();
        *(void **)var_16 = D_00472050;
        ((Obj *)var_16)->f5();
        var_16 += 0x24;
    } while (var_16 < (u8 *)arg0 + 0x3E0);
    arg0->unk0 = D_00474F80;
    arg0->unk230 = D_004752BC;
    return arg0;
}
