/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern s32 GetGameData_1fede0(void);
extern s32 HpGaugeTestFlags_31d3a0(s32, s32);
extern void HpGaugeDrawBarThin_31d440(s32, s32, s32, f32, f32, f32, f32);
extern f32 HpGaugeGetSlotAlpha_31e330(s32, s32);
extern void HpGaugeClearTimer_31e530(s32, s32);
extern void HpGaugeSetTargetRatio_31e5c0(s32, s32, f32);
extern f32 HpGaugeGetSize_31e5e0(s32, s32);
extern f32 HpGaugeGetDisplayedRatio_31e600(s32, s32);
extern s32 HpGaugeGetSlotState_31e660(s32, s32);
extern s32 HpGaugeGetHideStep_31e680(s32, s32);
extern void HpGaugeGetTimer_31e6a0(s32, s32);
extern s32 HpGaugeGetId_31e6c0(s32, s32);
extern void ** ActorCastToUnitBase_3b87f0(s32, int, int, int);
extern s32 ActorFindById_3eb8d0(s32, s32);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xF0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x128, x0); }
};
s32 HpGaugeDrawAllThin_31dff0(s32 arg0) {
    s32 var_19;
    f32 temp_f22;
    f32 temp_f21;
    s32 temp_18;
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_17;
    void **temp_2_3;
    s32 temp_2;
    s32 temp_2_2;
    f32 temp_f0;
    f32 var_f20;

    if (HpGaugeTestFlags_31d3a0(arg0, 2) != 0) {
        var_19 = 0;
        do {
            temp_18 = ((short)HpGaugeGetId_31e6c0(arg0, var_19));
            temp_2 = GetGameData_1fede0();
            if (temp_2 != 0) {
                temp_2_2 = ActorFindById_3eb8d0(temp_2, temp_18);
                if (temp_2_2 != 0) {
                    temp_2_3 = ActorCastToUnitBase_3b87f0(temp_2_2, 0, 0, 0);
                    if (temp_2_3 != NULL) {
                        temp_16 = ((VC_0 *)(temp_2_3))->f();
                        { s32 dd = ((VC_1 *)(temp_2_3))->f(1); temp_f22 = (f32) temp_16 / (f32) dd; }
                        HpGaugeSetTargetRatio_31e5c0(arg0, var_19, temp_f22);
                        if (temp_f22 <= 0.0f) {
                            HpGaugeClearTimer_31e530(arg0, var_19);
                        }
                        HpGaugeGetTimer_31e6a0(arg0, var_19);
                        temp_17 = ((short)HpGaugeGetHideStep_31e680(arg0, var_19));
                        temp_16_2 = ((unsigned char)HpGaugeGetSlotState_31e660(arg0, var_19));
                        temp_f21 = HpGaugeGetDisplayedRatio_31e600(arg0, var_19);
                        var_f20 = HpGaugeGetSlotAlpha_31e330(arg0, var_19);
                        temp_f0 = HpGaugeGetSize_31e5e0(arg0, var_19);
                        if ((temp_18 != -1) && (temp_16_2 != 0)) {
                            if (temp_16_2 != 2) {
                                var_f20 = 1.0f;
                            }
                            HpGaugeDrawBarThin_31d440(arg0, temp_18, temp_17, temp_f22, temp_f21, temp_f0, var_f20);
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
