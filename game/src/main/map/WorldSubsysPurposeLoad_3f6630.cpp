#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VTA {
    u8 pad[0x20];
    void (*unk20)(void *);
} VTA;

typedef struct VTD {
    u8 pad[0x1C];
    void (*unk1C)(void *, s32, s32, s32);
} VTD;

extern s32 D_00465890[4];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    void f() { VCM0(void, 0x20); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    void f() { VCM0(void, 0x20); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    void f() { VCM0(void, 0x20); }
};
class VC_3 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void f(s32 x0, s32 x1, s32 x2) { VCM(void, (void *, s32, s32, s32), 0x1C, x0, x1, x2); }
};
s32 WorldSubsysPurposeLoad_3f6630(u8 *arg0, s32 arg1, s32 pad, s32 arg3) {
    VTA **temp_4;
    VTA **temp_4_2;
    VTA **temp_4_3;
    VTD **temp_4_4;

    if (arg1 == 0) {
        return 0;
    }
    if (!(*(s32 *)(arg0 + 0) != 0)) {
        return 0;
    }
    *(s32 *)(arg0 + 8) = arg3;
    temp_4 = *(VTA ***)(arg0 + 0xC);
    if (temp_4 != NULL) {
        ((VC_0 *)(temp_4))->f();
    }
    temp_4_2 = *(VTA ***)(arg0 + 0x10);
    if (temp_4_2 != NULL) {
        ((VC_1 *)(temp_4_2))->f();
    }
    temp_4_3 = *(VTA ***)(arg0 + 0x14);
    if (temp_4_3 != NULL) {
        ((VC_2 *)(temp_4_3))->f();
    }
    temp_4_4 = *(VTD ***)(arg0 + 0x18);
    if (temp_4_4 != NULL) {
        ((VC_3 *)(temp_4_4))->f(arg1, D_00465890[0] != 0, 0);
    }
    return 1;
    return 0;
}

}
