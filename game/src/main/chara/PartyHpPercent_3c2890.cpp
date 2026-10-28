#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

extern void **CharaMgrPoolFindById_3a8c60(s32, s16);
extern void *D_00483890;

typedef s32 (*VtFn128)(void **, s32);
typedef s32 (*VtFnF0)(void **);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x128, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xF0); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x128, x0); }
};
class VC_3 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xF0); }
};
s32 PartyHpPercent_3c2890(u8 *arg0)
{
    s16 temp_21;
    s16 temp_5;
    s32 var_16;
    s32 var_19;
    s32 var_18;
    s32 var_17;
    void **temp_2;
    void *vtbl;

    if (D_00483890 == NULL) {
        return 0;
    }
    temp_21 = *(s16 *)(arg0 + 0x18C);
    var_19 = 0;
    var_18 = 0;
    for (var_17 = 0; var_17 < temp_21; var_17++) {
        temp_5 = *(s16 *)(arg0 + var_17 * 2 + 0x190);
        if (temp_5 >= 0) {
            temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), temp_5);
            if (temp_2 != NULL) {
                vtbl = *(void **)temp_2;
                var_19 += ((VC_0 *)(temp_2))->f(1);
                vtbl = *(void **)temp_2;
                var_18 += ((VC_1 *)(temp_2))->f();
            }
        }
    }
    for (var_16 = 0; var_16 < 7; var_16++) {
        temp_5 = *(s16 *)(arg0 + var_16 * 2 + 0x196);
        if (temp_5 >= 0) {
            temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), temp_5);
            if (temp_2 != NULL) {
                vtbl = *(void **)temp_2;
                var_19 += ((VC_2 *)(temp_2))->f(1);
                vtbl = *(void **)temp_2;
                var_18 += ((VC_3 *)(temp_2))->f();
            }
        }
    }
    return (s32)(100.0f * ((f32)var_18 / (f32)var_19));
}

}
