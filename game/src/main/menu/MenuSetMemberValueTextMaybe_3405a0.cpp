#include "types.h"

class Obj405a0 {
public:
    VC_VPTR_MEMBER;   
       
       
       
       
     
    s32 v60() { return VCM0(s32, 0x60); }
};

typedef struct Item2_405a0 {
    u8 pad0[0x28];
    void *unk28;
} Item2_405a0;

typedef struct Item16_405a0 {
    u8 pad0[4];
    void *unk4;
    u8 pad8[4];
    s32 unkC;
} Item16_405a0;

typedef struct S0_405a0 {
    u8 pad0[0x5C];
    s32 unk5C;
} S0_405a0;

extern "C" {
extern void Sprintf_1343b8(void *, s32, s32);
extern void *GetGameData_1fede0(void);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern Item2_405a0 *UiFindWidget_290460(s32, s32);
extern Obj405a0 *PoolGetUsedElem_36acb0(s32, s32);
extern s32 PartyGetSlotId_3c3120(s32, s32);
extern s32 D_004823D8;
extern u8 D_004E8920[0x400];
}

extern "C" s32 MenuSetMemberValueTextMaybe_3405a0(S0_405a0 *arg0, s32 arg1) {
    s32 temp_18;
    s32 temp_2_2;
    Obj405a0 *temp_2_3;
    Item16_405a0 *temp_16;
    void *temp_17;
    Item2_405a0 *temp_2;

    temp_17 = GetGameData_1fede0();
    temp_2 = UiFindWidget_290460(arg0->unk5C, 0x18C);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_16 = (Item16_405a0 *)temp_2->unk28;
    if (temp_16 == NULL) {
        return 0;
    }
    temp_2_2 = PartyGetSlotId_3c3120(*(s32 *)((u8 *)temp_17 + 0x18), arg1);
    temp_2_3 = PoolGetUsedElem_36acb0(*(s32 *)(*(u8 **)((u8 *)temp_17 + 0x14) + 8), temp_2_2);
    if (temp_2_3 == NULL) {
        return 0;
    }
    temp_18 = temp_2_3->v60();
    Sprintf_1343b8(D_004E8920, MsgTableLookup_28aa30(D_004823D8, 0x103B), temp_18);
    temp_16->unk4 = D_004E8920;
    if (temp_2_2 == 8) {
        temp_16->unkC = 0xFF202020;
    } else {
        temp_16->unkC = 0xFF303030;
    }
    return 1;
}
