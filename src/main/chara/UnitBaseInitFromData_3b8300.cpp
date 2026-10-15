#include "types.h"

typedef struct {
    u16 a;
    u16 b;
} Info;

class Obj {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual s32 fD4();
    virtual Info *fD8();
    u8 pad4[0xC];
    s16 m10;
    u8 pad12[2];
    s32 m14;
    s16 m18;
    u8 pad1A[2];
    s32 m1C[2];
    s16 m24[2];
    u8 pad28[4];
    s16 m2C[2];
    s16 m30[2];
    s16 m34[2];
    s16 m38[2];
    s32 m3C[2];
    s32 m44[2];
    s32 m4C[2];
    s16 m54[5][2];
    s16 m68[8][2];
    s16 m88[8][2];
    s16 mA8[4][2];
    u8 padB8[0xC8 - 0xB8];
    s64 mC8;
    f32 mD0[32];
    s16 m150[32];
    s16 m190;
    s16 m192;
    s16 m194;
    u8 pad196[2];
    s32 m198;
    u8 b19C_0 : 1;
    u8 b19C_r : 7;
    u8 pad19D[0x1C8 - 0x19D];
    u8 b1C8_0 : 1;
    u8 b1C8_1 : 1;
    u8 b1C8_2 : 1;
    u8 b1C8_r : 5;
    u8 pad1C9[3];
    f32 m1CC;
    f32 m1D0;
    s16 m1D4;
    s16 m1D6;
    s16 m1D8;
};

extern "C" {
extern s32 UnitSetId_3b8a30(...);
extern const s32 D_00465900[4];
extern const s32 D_00465910[4];
extern const s32 D_00465920[4];
}

extern "C" s32 UnitBaseInitFromData_3b8300(Obj *self)
{
    Info *info;
    s32 i;
    s32 j;
    s32 f;

    self->m10 = 1;
    if ((u8)UnitSetId_3b8a30() == 0) {
        return 0;
    }
    if (self->fD4() == 0) {
        return 0;
    }
    info = self->fD8();
    if (info == NULL) {
        return 0;
    }
    self->m14 = info->a;
    self->m18 = info->b;
    for (i = 0; i < 2; i++) {
        self->m1C[i] = info->a;
        self->m24[i] = info->b;
        self->m2C[i] = 0;
        self->m30[i] = 0;
        self->m34[i] = 0;
        self->m38[i] = 0;
        self->m3C[i] = 0;
        self->m44[i] = 0;
        self->m4C[i] = 0;
        for (j = 0; j < 5; j++) {
            self->m54[j][i] = 0;
        }
        for (j = 0; j < 8; j++) {
            self->m68[j][i] = 0;
        }
        for (j = 0; j < 7; j++) {
            self->m88[j][i] = 0;
        }
        for (j = 0; j < 4; j++) {
            self->mA8[j][i] = 0;
        }
    }
    self->mC8 = 0;
    for (i = 0; i < 32; i++) {
        self->mD0[i] = 0.0f;
        self->m150[i] = -1;
    }
    self->m190 = D_00465900[0];
    self->m192 = D_00465910[0];
    self->m194 = D_00465920[0];
    self->m198 = -1;
    f = 0;
    self->b19C_0 = f;
    self->b1C8_1 = f;
    self->b1C8_2 = f;
    self->m1CC = 0.0f;
    self->m1D0 = 0.0f;
    self->m1D4 = 0;
    self->m1D6 = 0;
    self->m1D8 = 0;
    return 1;
}
