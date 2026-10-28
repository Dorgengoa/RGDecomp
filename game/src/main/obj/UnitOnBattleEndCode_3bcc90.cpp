#include "types.h"
#pragma opt_propagation off

extern "C" {
class A {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 mbc() { return VCM0(s32, 0xBC); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void m1a8(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A8, a0, a1, a2); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void m2b0(s32 a0, bool a1, s32 a2) { VCM(void, (void *, s32, bool, s32), 0x2B0, a0, a1, a2); }
    void m2b4(s32 a0) { VCM(void, (void *, s32), 0x2B4, a0); }
};
class B {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 m388() { return VCM0(s32, 0x388); }
};

extern void BattleRecordDefeat_3a3410(void *, s32, s32, s32, s32);
extern B *PartyGetLeaderChara_3c2820(s32);
extern void *D_00483818;

s32 UnitOnBattleEndCode_3bcc90(A *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    B *temp_2;
    s32 r;
    s32 c1;
    s32 c2;

    if (D_00483818 == NULL) {
        return 0;
    }
    arg0->m1a8(1, 1, 1);
    if (!(*(u8 *)((u8 *)*(void **)((u8 *)D_00483818 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if ((arg1 == 1) && (arg0->mbc() != 0)) {
        if (arg2 != 0) {
            arg0->m2b0(0, !(arg4 != 0), arg4);
        } else {
            arg0->m2b4(0);
        }
        if (arg3 != 0) {
            temp_2 = PartyGetLeaderChara_3c2820(*(s32 *)((u8 *)D_00483818 + 0x18));
            if (temp_2 != NULL) {
                r = temp_2->m388();
                c2 = *(s32 *)((u8 *)temp_2 + 0xC);
                c1 = *(s32 *)((u8 *)arg0 + 0xC);
                BattleRecordDefeat_3a3410(*(void **)((u8 *)D_00483818 + 0x20), c1, c2, r, 0);
            } else {
                BattleRecordDefeat_3a3410(*(void **)((u8 *)D_00483818 + 0x20), *(s32 *)((u8 *)arg0 + 0xC), -1, 0, 0);
            }
        }
    }
    return 1;
}

}
