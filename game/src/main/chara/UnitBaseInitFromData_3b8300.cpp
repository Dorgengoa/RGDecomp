/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    u16 a;
    u16 b;
} Info;

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 fD4() { return VCM0(s32, 0xD4); }
    Info * fD8() { return VCM0(Info *, 0xD8); }
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
extern s32 UnitSetId_3b8a30(void *, int);
extern s32 D_00465900[4];
extern s32 D_00465910[4];
extern s32 D_00465920[4];
}

extern "C" s32 UnitBaseInitFromData_3b8300(Obj *self, int rgp_a1)
{
    Info *info;
    s32 i;
    s32 j;
    s32 f;

    self->m10 = 1;
    if ((u8)UnitSetId_3b8a30((void *)self, (int)rgp_a1) == 0) {
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
