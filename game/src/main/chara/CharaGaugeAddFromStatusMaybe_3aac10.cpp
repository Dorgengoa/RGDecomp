#pragma opt_common_subs off
/* PARK: length 0x154 vs retail 0x144 (0x10 over) after 1 round. Not re-tried. */
#include "types.h"
#undef NULL
#define NULL 0
class Self { public:
VC_VPTR_MEMBER;












































































































































































































































































































s32 ready() { return VCM0(s32, 0x4BC); }




s32 limit() { return VCM0(s32, 0x4D0); }
};
extern "C" {

extern void FieldHudAllySuggestRefreshMaybe_203c70(s32 arg0);
extern void StatusEntryClearIfActive_3a14d0(s32 arg0, void *arg1);
extern void *CharaSysStatusFind_3a16f0(s32 arg0, s32 arg1, s32 arg2);
extern s32 CharaIsPartyLeader_3ae1a0(void *arg0);
extern s32 BtlElemParamGetGaugeThreshold_3f9480(s32 arg0, s32 arg1);
extern void *D_00483818;
extern s32 D_00483824;

s32 CharaGaugeAddFromStatusMaybe_3aac10(void *arg0, s32 arg1)
{
    s32 temp_2_2; s32 threshold;
    s8 var_2;
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_4;
    s32 var_17;
    void *temp_2;

    temp_2 = CharaSysStatusFind_3a16f0(D_00483824, arg1, 0);
    if(temp_2==NULL) return 0;
    {
        temp_16 = *(u8 *)((u8 *)temp_2 + 0x1);
        StatusEntryClearIfActive_3a14d0(D_00483824, temp_2);
        if(((Self *)arg0)->ready()<=0) return 0;
        {
            temp_2_2 = ((Self *)arg0)->limit();
            temp_4 = *(u8 *)((u8 *)arg0 + 0x4BD);
            if(temp_4>=temp_2_2) return *(u8 *)((u8 *)arg0+0x4be);
            {
                *(u8 *)((u8 *)arg0 + 0x4BD) = (u8) (temp_4 + (temp_16 & 0xFF));
                if ((s32) *(u8 *)((u8 *)arg0 + 0x4BD) >= temp_2_2) {
                    *(u8 *)((u8 *)arg0 + 0x4BD) = (u8) temp_2_2;
                }
                temp_16_2 = *(u8 *)((u8 *)arg0 + 0x4BE);
                var_17 = 1;
                do {
                    threshold=BtlElemParamGetGaugeThreshold_3f9480(*(s32 *)((u8 *)*(void **)((u8 *)*(void **)((u8 *)D_00483818 + 0x8) + 0x54) + 0x8), var_17);
                    if ((s32) *(u8 *)((u8 *)arg0 + 0x4BD) >= threshold) {
                        *(u8 *)((u8 *)arg0 + 0x4BE) = var_17;
                    }
                    var_17 += 1;
                } while (var_17 <= 3);
                if ((s32) temp_16_2 < (s32) *(u8 *)((u8 *)arg0 + 0x4BE)) {
                    if(CharaIsPartyLeader_3ae1a0(arg0)!=0) { *(s8 *)((u8 *)arg0+0x4bf)=2; }
                    else { *(s8 *)((u8 *)arg0+0x4bf)=3; }
                }
                if (temp_16_2 != *(u8 *)((u8 *)arg0 + 0x4BE)) {
                    FieldHudAllySuggestRefreshMaybe_203c70(*(s32 *)((u8 *)arg0 + 0xC));
                }
            }
            return *(u8 *)((u8 *)arg0 + 0x4BE);
        }
        return 0;
    }
    return 0;
}

}
