/* rgp:protos */
#line 1
#include "types.h"

class VC3a7500 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 count() { return VCM0(s32, 0x2C4); }
    void * get(s32 a0) { return VCM(void *, (void *, s32), 0x2C8, a0); }
};

extern "C" {
extern s32 StrNotEqual_1f5300(s8 *, void *);
extern s32 EquipSlotGetRecId_3a0760(void *);
extern s8 *EquipSlotGetRecName_3a07a0(void *);
extern s32 ExecInfoInitFromEquipSlot_3a7690(s32, s32, s32, s32);
extern VC3a7500 * ActorFindById_3eb870(s32, int);
extern s32 D_004837B0;

s32 ExecInfoInitFromEquipSlotByName_3a7500(s32 arg0, s32 arg1, s8 *arg2, s32 arg3)
{
    s32 temp_17;
    VC3a7500 *temp_2;
    s32 var_20;
    s32 var_3;
    s8 *temp_2_3;
    s32 var_19;
    void *temp_2_2;

    if (D_004837B0 == 0) {
        return 0;
    }
    if (arg2 == NULL) {
        return 0;
    }
    temp_2 = ActorFindById_3eb870(D_004837B0, (int)arg1);
    if (temp_2 == NULL) {
        return 0;
    }
    var_20 = -1;
    temp_17 = temp_2->count();
    var_19 = 0;
    while (var_19 < temp_17) {
        temp_2_2 = temp_2->get(var_19);
        if ((temp_2_2 != NULL) && (*(s32 *)((u8 *)temp_2_2 + 0x4) != 0) &&
            ((temp_2_3 = EquipSlotGetRecName_3a07a0(temp_2_2)) != NULL)) {
            var_3 = *temp_2_3 != *arg2;
            if (var_3 == 0) {
                var_3 = StrNotEqual_1f5300(temp_2_3 + 1, arg2 + 1) != 0;
            }
            if (!(var_3 & 0xFF)) {
                var_20 = EquipSlotGetRecId_3a0760(temp_2_2);
                break;
            }
        }
        var_19 += 1;
    }
    return ExecInfoInitFromEquipSlot_3a7690(arg0, arg1, var_20, arg3);
}
}
