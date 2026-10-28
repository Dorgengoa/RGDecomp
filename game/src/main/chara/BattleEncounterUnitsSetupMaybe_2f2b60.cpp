/* rgp:protos */
#line 1
/* main s22: 1 WRONG ACCESS WIDTH(s) corrected from retail's own
   opcode (same registers + offset, different opcode -- a type defect no
   colouring lever can reach).  42 -> improved; still parked. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

extern void GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern void GetCharaResMgr_1fdb60(void);
extern void * GetGameData_1fede0(void);
extern void CharaSetAttachNodeName_213860(void *, s32);
extern void CharaSetAttachParentId_213880(void *, s32);
extern void CharaSetAppearMode_213fb0(void *, s32, s32);
extern void *ActionMgrFindById_233b50(s32, s32);
extern void GetEffectMgr_2d9040(void);
extern s32 UnitAddMonCharaMaybe_2f3160(s32, long long);

typedef s32 (*Fn5C)(void *);
typedef s32 (*Fn3EC)(void *);
typedef void *(*Fn3F4)(void *, s32);
typedef s32 (*Fn3DC)(void *, s32, s32);
typedef s32 (*Fn3E0)(void *);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x5C); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x3EC); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * f(s32 x0) { return VCM(void *, (void *, s32), 0x3F4, x0); }
};
class VC_3 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x5C); }
};
class VC_4 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0, s32 x1) { return VCM(s32, (void *, s32, s32), 0x3DC, x0, x1); }
};
class VC_5 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x3E0); }
};
s32 BattleEncounterUnitsSetupMaybe_2f2b60(void)
{
    s32 var_21;
    u8 *temp_16_2;
    s32 temp_22;
    u8 *temp_20;
    s32 temp_17;
    s32 temp_17_2;
    s32 temp_23;
    s32 temp_3;
    s32 temp_5;
    s32 temp_6;
    s32 temp_7;
    u8 *temp_16;
    s32 var_19;
    u8 *temp_2;
    u8 *temp_2_2;
    u8 *temp_2_3;
    void *vtbl;

    temp_16 = (u8 *)GetGameData_1fede0();
    temp_22 = GetActionMgr_1fdb50();
    GetCharaResMgr_1fdb60();
    GetEffectMgr_2d9040();
    GetCurrentScene_1f5be0();
    temp_16_2 = *(u8 **)(*(u8 **)(temp_16 + 0x20) + 0x238);
    if (temp_16_2 == NULL) {
        return 0;
    }
    var_21 = 0;
    while (var_21 < *(s16 *)(temp_16_2 + 0x44)) {
        temp_20 = *(u8 **)(temp_16_2 + var_21 * 8 + 0x4C);
        if (temp_20 != NULL) {
            temp_17 = *(s32 *)(temp_20 + 0xC);
            vtbl = *(void **)temp_20;
            if (UnitAddMonCharaMaybe_2f3160(temp_17, (long long)(((VC_0 *)(temp_20))->f())) != 0) {
                temp_2 = (u8 *)ActionMgrFindById_233b50(temp_22, *(s32 *)(temp_20 + 0xC));
                if (temp_2 != NULL) {
                    temp_7 = *(s32 *)(temp_2 + 0xA44) | 0x01000000;
                    *(s32 *)(temp_2 + 0xA44) = temp_7;
                    CharaSetAppearMode_213fb0(temp_2, 2, (var_21 * 0xF) + 1);
                    vtbl = *(void **)temp_20;
                    temp_23 = ((VC_1 *)(temp_20))->f();
                    var_19 = 0;
                    while (var_19 < temp_23) {
                        vtbl = *(void **)temp_20;
                        temp_2_2 = (u8 *)((VC_2 *)(temp_20))->f(var_19);
                        temp_17_2 = *(s32 *)(temp_2_2 + 0xC);
                        vtbl = *(void **)temp_2_2;
                        if (UnitAddMonCharaMaybe_2f3160(temp_17_2, (long long)(((VC_3 *)(temp_2_2))->f())) != 0) {
                            temp_2_3 = (u8 *)ActionMgrFindById_233b50(temp_22, *(s32 *)(temp_2_2 + 0xC));
                            if (temp_2_3 != NULL) {
                                temp_6 = *(s32 *)(temp_2_3 + 0xA44);
                                temp_5 = temp_6 | 0x01000000;
                                temp_3 = temp_5 | 0x80000;
                                *(s32 *)(temp_2_3 + 0xA44) = temp_5;
                                *(s32 *)(temp_2_3 + 0xA44) = temp_3;
                                *(s32 *)(temp_2_3 + 0xA44) = (s32) (temp_3 | 0x40000000);
                                vtbl = *(void **)temp_2_2;
                                CharaSetAttachParentId_213880(temp_2_3, ((VC_4 *)(temp_2_2))->f(temp_5, temp_6));
                                vtbl = *(void **)temp_2_2;
                                CharaSetAttachNodeName_213860(temp_2_3, ((VC_5 *)(temp_2_2))->f());
                            }
                        }
                        var_19 += 1;
                    }
                }
            }
        }
        var_21 += 1;
    }
    return 1;
    return 0;
}

}
