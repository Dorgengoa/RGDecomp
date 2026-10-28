#include "types.h"

typedef struct E8_2C1B {
    u8 b[8];
} E8_2C1B;

typedef struct Ctx2C1B {
    u8    pad000[0x1C];
    void *mOFF;
} Ctx2C1B;

class O2C1B {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v145() { return VCM0(s32, 0x24C); }
};

extern "C" void *D_004DB928[];

extern "C" void *ScriptSlotGetInt_2cc9c0(E8_2C1B *p);
extern "C" Ctx2C1B *GetGameData_1fede0(void);
extern "C" O2C1B *ObjFindById_3bb3a0(void *a, void *x);
extern "C" void ScriptSlotStoreIntRef_2cc900(E8_2C1B *p, s32 f);

extern "C" s32 AiCmdObjGetStatusFxA_2c1cb0(E8_2C1B *p, s32 mode)
{
    void *x;
    O2C1B *o;

    x = D_004DB928[0];
    if (mode == 2) {
        x = ScriptSlotGetInt_2cc9c0(p++);
    }
    o = ObjFindById_3bb3a0(GetGameData_1fede0()->mOFF, x);
    if (o != 0 && o->v145() != 0) {
        ScriptSlotStoreIntRef_2cc900(p, 1);
    } else {
        ScriptSlotStoreIntRef_2cc900(p, 0);
    }
    return 1;
}
