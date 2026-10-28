/* MATCH (s41m). Stale pre-match note follows -- PARKED: 1 round trip: vtable calls through unk0 at 0x20/0x58; length 0x124 vs retail 0x128. */
#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off
extern "C" {

extern s32 ResidentFileReadLocalizedMaybe_1c2860(void *, s32, s32 *);
extern void strcat(void *, s32);
extern void strcpy(void *, s32);
extern s32 D_0047F990;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    void f() { VCM0(void, 0x20); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0, s32 x1, s32 x2) { return VCM(s32, (void *, s32, s32, s32), 0x58, x0, x1, x2); }
};
s32 DataTableLoadResidentBin_368d00(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
        s32 arg_h1;

    s32 spBC;
    u8 sp30[0x8C] __attribute__((aligned(16)));
    s32 var_8;
    void *temp_2;

    var_8 = arg4;
    if (*(s32 *)((u8 *)arg0 + 0x8) == 0) {
        return 0;
    }
    if ((arg1 == 0) && (*(s32 *)((u8 *)arg0 + 0xC) == 0)) {
        return 0;
    }
    temp_2 = *(void **)((u8 *)arg0 + 0x10);
    if (temp_2 == NULL) {
        return 0;
    }
    if (*(s32 *)((u8 *)temp_2 + 0x34) <= 0) {
        return 0;
    }
    if (var_8 == 0) {
        var_8 = *(s32 *)((u8 *)arg0 + 0x8);
    }
    if (var_8 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        *(s32 *)((u8 *)arg0 + 0xC) = arg1;
    }
    spBC = 0;
    if (arg3 > 0) {
        spBC = arg3;
    } else {
        arg_h1 = var_8;
        strcpy(sp30, var_8);
        strcat(sp30, D_0047F990);
        if (!(ResidentFileReadLocalizedMaybe_1c2860(sp30, *(s32 *)((u8 *)arg0 + 0xC), &spBC) & 0xFF) || (spBC <= 0)) {
            ((VC_0 *)(arg0))->f();
            return 0;
        }
    }
    return ((VC_1 *)(arg0))->f(*(s32 *)((u8 *)arg0 + 0xC), spBC, arg2);
    return 0;
}

}
