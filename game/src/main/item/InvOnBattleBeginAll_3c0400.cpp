#include "types.h"

extern "C" {
class Item {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fF4() { VCM0(void, 0xF4); }
};

struct Bf { u8 b0 : 1; u8 b1 : 1; u8 rest : 6; };
struct A3 { u8 pad[0x168]; s32 unk168; };
extern Item *PoolGetUsedElem_36acb0(s32, s32);
extern s32 D_00465B50[4];
extern void *D_00483890;

s32 InvOnBattleBeginAll_3c0400(struct A3 *arg0)
{
    s32 temp_16;
    s32 var_17;
    Item *temp_2;

    if (D_00483890 == NULL) {
        return 0;
    }
    if (*(u8 *)(*(u8 **)((u8 *)D_00483890 + 0x20) + 0x24C) & 1) {
        return 0;
    }
    if (arg0->unk168 == 0) {
        return 0;
    }
    temp_16 = D_00465B50[0];
    for (var_17 = 0; var_17 < temp_16; var_17++) {
        temp_2 = PoolGetUsedElem_36acb0(arg0->unk168, var_17);
        if (temp_2 != NULL && ((struct Bf *)((u8 *)temp_2 + 0xA))->b1 == 0) {
            temp_2->fF4();
        }
    }
    return 1;
}

}
