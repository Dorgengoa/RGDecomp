/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0

class Sub003AA080 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(f32 x) { VCM(void, (void *, f32), 0x74, x); }
};
class Obj003AA080 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void g() { VCM0(void, 0x38); }
};

typedef struct {
    u8 pad0[0x10];
    f32 unk10;
} Obj498003AA080;

extern "C" {
s32 UnitBaseUpdate_3b0bf0(void *, float);                                 /* extern */
extern u8 D_00465930[0x400];
extern s32 D_00483820;
}

typedef struct {
    u8 pad0[0x23C];
    u8 unk23C;
    u8 pad23D[0x498 - 0x23D];
    Obj498003AA080 *unk498;
    s16 unk49C;
} F003AA080;
#define F(p) (pf)
#define O(p, off, T) (*(T *)((u8 *)(p) + (off)))

extern "C" s32 CharaUpdate_3aa080(Obj003AA080 *arg0, f32 fparg0) {
    F003AA080 *pf = (F003AA080 *)arg0;
    s16 temp_3;
    s32 var_16;
    Obj498003AA080 *temp_2_2;

    if (!(UnitBaseUpdate_3b0bf0((void *)arg0, (float)fparg0) & 0xFF)) {
        return 0;
    }
    if (D_00483820 == 0) {
        return 0;
    }
    if (F(arg0)->unk23C & 1) {
        temp_3 = F(arg0)->unk49C;
        if (temp_3 < (*(s32 *)D_00465930)) {
            F(arg0)->unk49C = (s16) (temp_3 + 1);
        }
    }
    var_16 = 0;
    do {
        ((Sub003AA080 *)((u8 *)arg0 + 0x308 + var_16 * 0x28))->f(fparg0);
        var_16 += 1;
    } while (var_16 < 0xA);
    temp_2_2 = F(arg0)->unk498;
    if (temp_2_2 != NULL && temp_2_2->unk10 <= 0.0f) {
        F(arg0)->unk498 = NULL;
        arg0->g();
    }
    return 1;
}
