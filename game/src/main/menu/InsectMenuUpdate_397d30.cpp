#include "types.h"

typedef struct {
    u8 pad0[4];
    s16 unk4;
} Sub18_00397D30;

typedef struct {
    u8 pad0[0x18];
    Sub18_00397D30 *unk18;
} Sub4_00397D30;

typedef struct {
    u8 pad0[4];
    Sub4_00397D30 *unk4;
} Obj00397D30;

class Obj483518_00397D30 {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v15(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
};

extern "C" {
void UiEntryListSelectByTag_28ea90(void *, s32, s32);
void StateMachineUpdate_28ed70(void *);
void StateMachineSetState_28ede0(void *, s32, s32);
void UiUpdateWidgets_2913a0(void *);
f32 GetSceneTimeStep_293350();
void InsectMenuResLoadPoll_398420();
s32 CageRecCountTriggered_3d08c0(Sub4_00397D30 *);
Obj00397D30 *GetSelectedInsectEntryMaybe_206ad0();
}
extern "C" s16 D_0047FF40;
extern "C" s16 D_0047FF4C;
extern "C" s32 D_004834F0;
extern "C" s16 D_00483504;
extern "C" s16 D_00483508;
extern "C" u8 D_0048350C;
extern "C" Obj483518_00397D30 *D_00483518;
extern "C" u8 D_0048352C;
extern "C" u8 D_004E95C0[0x400];
extern "C" u8 D_004E95E0[0x400];

extern "C" void InsectMenuUpdate_397d30(void) {
    Obj00397D30 *temp_2;

    if (D_00483504 != 0) {
        if ((D_00483508 == 1) && (D_0047FF40 == 1)) {
            D_00483504 = 2;
            D_0047FF40 = 0;
            if (D_0047FF4C == 0) {
                StateMachineSetState_28ede0(&D_004834F0, 0x7532, 0);
            } else {
                UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7534, 0);
                temp_2 = GetSelectedInsectEntryMaybe_206ad0();
                if (temp_2 == NULL) {
                    return;
                }
                if (CageRecCountTriggered_3d08c0(temp_2->unk4) > 0) {
                    StateMachineSetState_28ede0(&D_004834F0, 0x7531, 0);
                } else if (temp_2->unk4->unk18->unk4 > 0) {
                    StateMachineSetState_28ede0(&D_004834F0, 0x7539, 1);
                } else {
                    StateMachineSetState_28ede0(&D_004834F0, 0x7535, 1);
                }
            }
        }
        InsectMenuResLoadPoll_398420();
        UiUpdateWidgets_2913a0(D_004E95C0);
        StateMachineUpdate_28ed70(&D_004834F0);
        if ((D_0048352C != 0) && (D_0048350C != 0)) {
            D_00483518->v15(GetSceneTimeStep_293350());
        }
    }
}
