#include "types.h"

class Obj25b1b0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void call(s32 flag) { VCM(void, (void *, s32), 0x464, flag); }
};

struct Root25b1b0 {
    u8 pad00[0x14];
    void *m14;
};

struct E25b1b0 {
    u8 b[8];
};

extern "C" struct Root25b1b0 *GetGameData_1fede0(void);
extern "C" void *ScriptGetInt_26a2a0(struct E25b1b0 *q);
extern "C" class Obj25b1b0 *CharaMgrPoolFindById_3a8c60(void *a, void *b);

extern "C" s32 EvCmdCharaSetAltFormFlagMaybe_25b1b0(struct E25b1b0 *q, s32 kind)
{
    struct Root25b1b0 *g;
    void *a;
    void *b;
    class Obj25b1b0 *o;

    if (kind != 2) {
        return 0;
    }
    g = GetGameData_1fede0();
    a = ScriptGetInt_26a2a0(q++);
    o = CharaMgrPoolFindById_3a8c60(g->m14, a);
    if (o == 0) {
        return 0;
    }
    b = ScriptGetInt_26a2a0(q);
    o->call(b != 0);
    return 1;
}
