#include "types.h"

class Obj2c7120 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void call(s32 flag) { VCM(void, (void *, s32), 0x238, flag); }
};

struct Root2c7120 {
    u8 pad00[0x1C];
    void *m1C;
};

struct E2c7120 {
    u8 b[8];
};

extern "C" struct Root2c7120 *GetGameData_1fede0(void);
extern "C" void *ScriptSlotGetInt_2cc9c0(struct E2c7120 *q);
extern "C" class Obj2c7120 *ObjFindById_3bb3a0(void *a, void *b);

extern "C" s32 AiCmdObjSetActiveMaybe_2c7120(struct E2c7120 *q)
{
    struct Root2c7120 *g;
    void *a;
    void *b;
    s32 flag;
    class Obj2c7120 *o;

    g = GetGameData_1fede0();
    a = ScriptSlotGetInt_2cc9c0(q++);
    b = ScriptSlotGetInt_2cc9c0(q);
    flag = (b != 0);
    o = ObjFindById_3bb3a0(g->m1C, a);
    if (o != 0) {
        o->call(flag);
    }
    return 1;
}
