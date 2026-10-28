/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern s32 CharaGetActionKind_213840(s32);
extern s32 CharaGetAttachParentId_213890(s32);
extern void CharaJudgeObjCreate_213cf0(s32, s32, void *, f32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern f32 ScriptArgGetFloat_302cf0(s32);
extern s32 EquipSlotGetRecId_3a0760(s32);
}
class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f470() { return VCM0(s32, 0x470); }
};
extern "C" VObj *CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" u8 D_0045D638[0x400];
extern "C" u8 D_0045D650[0x400];
extern "C" u8 D_0045D670[0x400];
extern "C" u8 D_0045D690[0x400];
extern "C" u8 D_0045D6B0[0x400];

extern "C" s32 CharaCmdJoThrow_22b570(s32 *arg0, s32 arg1, s32 arg2)
{
    void *temp_19;
    VObj *obj;
    s32 temp_2_4;
    s32 temp_2_3;
    s32 temp_2;
    f32 var_f20;
    void *var_16;

    if ((arg2 != 1) && (arg2 != 2)) {
        return 0;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    if ((((short)CharaGetActionKind_213840(temp_2)) != 0x16) && (((short)CharaGetActionKind_213840(temp_2)) != 0x17)) {
        return 0;
    }
    var_f20 = 0.0f;
    if (arg2 > 1) {
        var_f20 = ScriptArgGetFloat_302cf0(arg1 + 5);
    }
    var_16 = D_0045D638;
    temp_19 = GetGameData_1fede0();
    obj = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)temp_19 + 0x14), CharaGetAttachParentId_213890(temp_2));
    if (obj != NULL) {
        temp_2_3 = obj->f470();
        if (temp_2_3 != 0) {
            switch (EquipSlotGetRecId_3a0760(temp_2_3)) {
            case 0x6F:
                var_16 = D_0045D650;
                break;
            case 0x70:
                var_16 = D_0045D670;
                break;
            case 0x32B:
                var_16 = D_0045D690;
                break;
            case 0x32C:
                var_16 = D_0045D6B0;
                break;
            }
        }
    }
    CharaJudgeObjCreate_213cf0(temp_2, ScriptArgGetStr_302cb0(arg1), var_16, var_f20);
    return 1;
}
