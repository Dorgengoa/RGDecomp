#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

extern void **ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e0b0(s32, s32);
extern s32 D_004644A8[];
extern s32 D_004657C0[];
extern u8 D_004657C8[0x400];
extern void DataTableCtor_41e9d0(...);
extern void DataTableCtor_41ef20(...);

typedef void (*Fn4C)(void **);
typedef void (*FnC)(void **, s32, s32, s32, s32);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x4C); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    void f(s32 x0, s32 x1, s32 x2, s32 x3) { VCM(void, (void *, s32, s32, s32, s32), 0xC, x0, x1, x2, x3); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x4C); }
};
class VC_3 {
public:
    VC_VPTR_MEMBER;
    void f(s32 x0, s32 x1, s32 x2, s32 x3) { VCM(void, (void *, s32, s32, s32, s32), 0xC, x0, x1, x2, x3); }
};
s32 WorldSubsysInit_41e580(void *__restrict arg0, s32 arg1, s32 arg2)
{
    void **var_18;
    void **var_21;
    s32 temp_22;
    s32 var_18_2;
    s32 var_22;
    s32 temp_23;
    s32 var_17;
    s32 temp_16;
    void **temp_2;
    void **temp_2_2;
    u8 *base;
    s32 var_17_2;
    void *vtbl;

    base = (u8 *)arg0;
    if (arg1 == 0) {
        return 0;
    }
    *(s32*)(base + 0x0) = arg1;
    temp_16 = D_004644A8[0];
    temp_2 = ConstructNewArray_100710(MemStackNew_14e0b0((temp_16 * 0x98) + 0x10, *(s32*)(base + 0x0)), (void *)&DataTableCtor_41ef20, 0, 0x98, temp_16);
    *(void ***)(base + 0x8) = temp_2;
    if (temp_2 == NULL) {
        return 0;
    }
    temp_2_2 = ConstructNewArray_100710(MemStackNew_14e0b0((temp_16 * 0x98) + 0x10, *(s32*)(base + 0x0)), (void *)&DataTableCtor_41e9d0, 0, 0x98, temp_16);
    *(void ***)(base + 0xC) = temp_2_2;
    if (temp_2_2 == NULL) {
        return 0;
    }
    var_18 = *(void ***)(base + 0x8);
    if (var_18 != NULL) {
        var_17 = 0;
        temp_23 = D_004657C0[0] != 0;
        while (var_17 < temp_16) {
            var_22 = arg1;
            if (arg2 != 0) {
                var_22 = arg2 + (var_17 * 0x58);
            }
            vtbl = *var_18;
            ((VC_0 *)(var_18))->f();
            vtbl = *var_18;
            ((VC_1 *)(var_18))->f(var_22, 0, temp_23, 0);
            var_17 += 1;
            var_18 += 0x98 / 4;
        }
    }
    var_21 = *(void ***)(base + 0xC);
    if (var_21 != NULL) {
        var_18_2 = 0;
        temp_22 = (*(s32 *)D_004657C8) != 0;
        while (var_18_2 < temp_16) {
            var_17_2 = arg1;
            if (arg2 != 0) {
                var_17_2 = arg2 + (var_18_2 * 0x58);
            }
            vtbl = *var_21;
            ((VC_2 *)(var_21))->f();
            vtbl = *var_21;
            ((VC_3 *)(var_21))->f(var_17_2, 0, temp_22, 0);
            var_18_2 += 1;
            var_21 += 0x98 / 4;
        }
    }
    return 1;
}

}
