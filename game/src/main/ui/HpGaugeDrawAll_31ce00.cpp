/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

/* ---- mechanical m2c draft (lane u31) -------------------------------------
   Produced by build/u31/gendraft.py from m2c --valid-syntax.  This is a
   STARTING POINT, not a match: every M2C_* macro below marks something m2c
   could not type or could not translate.  Replace them as the unit is worked.
   -------------------------------------------------------------------- */
typedef rg_u128 u128;
typedef rg_s128 s128;
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
void HpGaugeSetSlotAlpha_31e350(s32, s32, f32);                /* extern */
void HpGaugeClearTimer_31e530(s32, s32);                     /* extern */
void HpGaugeSetTargetRatio_31e5c0(s32, s32, f32);                /* extern */
f32 HpGaugeGetSize_31e5e0(s32, s32);                         /* extern */
f32 HpGaugeGetDisplayedRatio_31e600(s32, s32);                         /* extern */
s32 HpGaugeGetSlotState_31e660(s32, s32);                         /* extern */
s32 HpGaugeGetHideStep_31e680(s32, s32);                         /* extern */
M2C_UNK HpGaugeGetTimer_31e6a0(s32, s32);                     /* extern */
s32 HpGaugeGetId_31e6c0(s32, s32);                         /* extern */
s8 ** ActorCastToUnitBase_3b87f0(s32, int, int, int);                           /* extern */
s32 ActorFindById_3eb8d0(s32, s32);                         /* extern */
extern f32 D_0047D860;
extern f32 D_0047D864;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xBC); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x268); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x264); }
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
            temp_18 = ((short)HpGaugeGetId_31e6c0(arg0, var_19));
            temp_2 = GetGameData_1fede0();
            if (temp_2 != 0) {
                temp_2_2 = ActorFindById_3eb8d0(temp_2, temp_18);
                if (temp_2_2 != 0) {
                    temp_2_3 = (s8 **)(ActorCastToUnitBase_3b87f0(temp_2_2, 0, 0, 0));
                    if (temp_2_3 != NULL) {
                        if (((VC_0 *)(temp_2_3))->f() != 0) {
                            temp_16 = ((VC_1 *)(temp_2_3))->f();
                            hc0 = ((VC_2 *)(temp_2_3))->f();
                            temp_f22 = (f32) temp_16 / (f32) hc0;
                            HpGaugeSetTargetRatio_31e5c0(arg0, var_19, temp_f22);
                            if (!(temp_f22 < 1.0f)) {
                                if (((short)HpGaugeGetHideStep_31e680(arg0, var_19)) < 0) {
                                    HpGaugeSetSlotAlpha_31e350(arg0, var_19, D_0047D860 * HpGaugeGetSlotAlpha_31e330(arg0, var_19));
                                    HpGaugeClearTimer_31e530(arg0, var_19);
                                } else {
                                    if (((short)HpGaugeGetHideStep_31e680(arg0, var_19)) > 0) {
                                        HpGaugeSetSlotAlpha_31e350(arg0, var_19, HpGaugeGetSlotAlpha_31e330(arg0, var_19) - D_0047D864);
                                    }
                                }
                            }
                            HpGaugeGetTimer_31e6a0(arg0, var_19);
                            temp_17 = ((short)HpGaugeGetHideStep_31e680(arg0, var_19));
                            temp_16_2 = ((unsigned char)HpGaugeGetSlotState_31e660(arg0, var_19));
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
