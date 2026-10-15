#include "types.h"
extern "C" {

/* ---- mechanical m2c draft (lane u31) -------------------------------------
   Produced by build/u31/gendraft.py from m2c --valid-syntax.  This is a
   STARTING POINT, not a match: every M2C_* macro below marks something m2c
   could not type or could not translate.  Replace them as the unit is worked.
   -------------------------------------------------------------------- */
typedef unsigned __int128 u128;
typedef __int128 s128;
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK(x) (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

s32 GetGameData_1fede0();                                 /* extern */
M2C_UNK HpGaugeDrawBar_31c310(s32, s32, s32, f32, f32, f32, f32); /* extern */
s32 HpGaugeTestFlags_31d3a0(s32, M2C_UNK);                          /* extern */
f32 HpGaugeGetSlotAlpha_31e330(s32, s32);                         /* extern */
M2C_UNK HpGaugeSetSlotAlpha_31e350(s32, s32, f32);                /* extern */
M2C_UNK HpGaugeClearTimer_31e530(s32, s32);                     /* extern */
M2C_UNK HpGaugeSetTargetRatio_31e5c0(s32, s32, f32);                /* extern */
f32 HpGaugeGetSize_31e5e0(s32, s32);                         /* extern */
f32 HpGaugeGetDisplayedRatio_31e600(s32, s32);                         /* extern */
s32 HpGaugeGetSlotState_31e660(s32, s32);                         /* extern */
s32 HpGaugeGetHideStep_31e680(s32, s32);                         /* extern */
M2C_UNK HpGaugeGetTimer_31e6a0(s32, s32);                     /* extern */
s32 HpGaugeGetId_31e6c0(s32, s32);                         /* extern */
s8 **ActorCastToUnitBase_3b87f0(s32);                           /* extern */
s32 ActorFindById_3eb8d0(s32, s32);                         /* extern */
extern f32 D_0047D860;
extern f32 D_0047D864;

class VC_0 {
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
    virtual s32 f();
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
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual void d151();
    virtual s32 f();
};
class VC_2 {
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
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual s32 f();
};
s32 HpGaugeDrawAll_31ce00(s32 arg0) {
    s32 hc0;
    s32 var_19;
    s32 temp_18;
    f32 temp_f21;
    f32 temp_f22;
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_17;
    s8 **temp_2_3;
    s32 temp_2;
    s32 temp_2_2;
    f32 temp_f0;
    f32 temp_f20;

    if (HpGaugeTestFlags_31d3a0(arg0, 2) != 0) {
        var_19 = 0;
        do {
            temp_18 = HpGaugeGetId_31e6c0(arg0, var_19);
            temp_2 = GetGameData_1fede0();
            if (temp_2 != 0) {
                temp_2_2 = ActorFindById_3eb8d0(temp_2, temp_18);
                if (temp_2_2 != 0) {
                    temp_2_3 = (s8 **)(ActorCastToUnitBase_3b87f0(temp_2_2));
                    if (temp_2_3 != NULL) {
                        if (((VC_0 *)(temp_2_3))->f() != 0) {
                            temp_16 = ((VC_1 *)(temp_2_3))->f();
                            hc0 = ((VC_2 *)(temp_2_3))->f();
                            temp_f22 = (f32) temp_16 / (f32) hc0;
                            HpGaugeSetTargetRatio_31e5c0(arg0, var_19, temp_f22);
                            if (!(temp_f22 < 1.0f)) {
                                if (HpGaugeGetHideStep_31e680(arg0, var_19) < 0) {
                                    HpGaugeSetSlotAlpha_31e350(arg0, var_19, D_0047D860 * HpGaugeGetSlotAlpha_31e330(arg0, var_19));
                                    HpGaugeClearTimer_31e530(arg0, var_19);
                                } else {
                                    if (HpGaugeGetHideStep_31e680(arg0, var_19) > 0) {
                                        HpGaugeSetSlotAlpha_31e350(arg0, var_19, HpGaugeGetSlotAlpha_31e330(arg0, var_19) - D_0047D864);
                                    }
                                }
                            }
                            HpGaugeGetTimer_31e6a0(arg0, var_19);
                            temp_17 = HpGaugeGetHideStep_31e680(arg0, var_19);
                            temp_16_2 = HpGaugeGetSlotState_31e660(arg0, var_19);
                            temp_f21 = HpGaugeGetDisplayedRatio_31e600(arg0, var_19);
                            temp_f20 = HpGaugeGetSlotAlpha_31e330(arg0, var_19);
                            temp_f0 = HpGaugeGetSize_31e5e0(arg0, var_19);
                            if ((temp_18 != -1) && (temp_16_2 != 0)) {
                                HpGaugeDrawBar_31c310(arg0, temp_18, temp_17, temp_f22, temp_f21, temp_f0, temp_f20);
                                if (temp_17 < 0) {
                                    HpGaugeSetSlotAlpha_31e350(arg0, var_19, 1.0f);
                                }
                            }
                        } else {
                            HpGaugeSetSlotAlpha_31e350(arg0, var_19, 0.0f);
                            HpGaugeClearTimer_31e530(arg0, var_19);
                        }
                    }
                }
            }
            var_19 += 1;
        } while (var_19 < 0x10);
    }
    return 1;
}

}
