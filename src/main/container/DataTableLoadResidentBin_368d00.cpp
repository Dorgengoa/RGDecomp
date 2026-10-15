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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void f();
};
class VC_1 {
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
    virtual s32 f(s32 x0, s32 x1, s32 x2);
};
s32 DataTableLoadResidentBin_368d00(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
        s32 arg_h1;

    s32 spBC;
    u8 sp30[0x8C];
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
