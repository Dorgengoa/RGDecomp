#include "types.h"

class C0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v146(s32 a, s32 b) { VCM(void, (void *, s32, s32), 0x250, a, b); }
};

struct Root {
    u8 pad00[0x1C];
    void *m1C;
};

extern "C" void *D_004DB928 __attribute__((section(".data")));
struct Slot {
    s32 a;
    s32 b;
};

extern "C" void *ScriptSlotGetInt_2cc9c0(struct Slot *a);
extern "C" struct Root *GetGameData_1fede0(void);
extern "C" class C0 *ObjFindById_3bb3a0(void *a, void *b);

extern "C" s32 AiCmdObjSetStatusFxA_2c1d60(void *a0, s32 mode)
{
    void *x;
    void *y;
    class C0 *o;
    struct Slot *p;

    p = (struct Slot *)a0;
    x = D_004DB928;
    if (mode == 2) {
        x = ScriptSlotGetInt_2cc9c0(p++);
    }
    y = ScriptSlotGetInt_2cc9c0(p);
    o = ObjFindById_3bb3a0(GetGameData_1fede0()->m1C, x);
    if (o != 0) {
        o->v146(y != 0, 0);
    }
    return 1;
}
