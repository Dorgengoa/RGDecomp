#include "types.h"
extern "C" {

class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0) { VCM(void, (void *, s32), 0xFC, x0); }
};

typedef struct Flags { u8 b0 : 1; u8 b1 : 1; u8 rest : 6; } Flags;

extern VC *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern s32 D_00465B50[0x10];
extern void *D_00483890;

typedef struct O { u8 pad0[0x168]; s32 unk168; } O;

s32 InvOnBattleEndAll_3c01e0(O *arg0, s32 arg1)
{
    s32 n;
    s32 i;
    VC *p;

    if (D_00483890 == NULL) {
        return 0;
    }
    if (!(*(u8 *)((u8 *)*(void **)((u8 *)D_00483890 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if (arg0->unk168 == 0) {
        return 0;
    }
    n = D_00465B50[0];
    for (i = 0; i < n; i++) {
        p = PoolGetUsedElem_36acb0(arg0->unk168, i);
        if (p != NULL && ((Flags *)((u8 *)p + 0xA))->b1 == 0) {
            p->f(arg1);
        }
    }
    return 1;
}

}
