#include "types.h"

extern "C" {
extern s32 CharaIsInParty_3ae1d0(void *);
extern void *D_00483818;
}

class ClassA {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v_24() { VCM0(void, 0x68); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v_104(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A8, a0, a1, a2); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v_171(s32 a0) { VCM(void, (void *, s32), 0x2B4, a0); }
};

class ClassB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v_24(s32 a0) { VCM(void, (void *, s32), 0x68, a0); }
};

extern "C" s32 CharaOnBattleEndCode_3aa750(ClassA *arg0, s32 arg1) {
    s32 var_16;
    ClassB *temp_2;

    if (D_00483818 == NULL) {
        return 0;
    }
    arg0->v_104(1, 1, 1);
    if (!(*(u8 *)((u8 *)(*(u8 **)((u8 *)D_00483818 + 0x20)) + 0x24C) & 1)) {
        return 0;
    }
    var_16 = 0;
    do {
        temp_2 = (ClassB *)((u8 *)arg0 + (var_16 * 0x28) + 0x308);
        temp_2->v_24(arg1);
        var_16 += 1;
    } while (var_16 < 0xA);
    if ((arg1 == 2) && (CharaIsInParty_3ae1d0(arg0) != 0)) {
        arg0->v_171(0);
    }
    return 1;
}
