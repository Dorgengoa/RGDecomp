#include "types.h"

class Obj240a10 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void call(s32 flag) { VCM(void, (void *, s32), 0x464, flag); }
};

struct Root240a10 {
    u8 pad00[0x14];
    void *m14;
};

struct E240a10 {
    u8 b[8];
};

extern "C" struct Root240a10 *GetGameData_1fede0(void);
extern "C" void *ScriptGetInt_2490f0(struct E240a10 *q);
extern "C" class Obj240a10 *CharaMgrPoolFindById_3a8c60(void *a, void *b);

extern "C" s32 EvCmdCharaSetAltFormFlagMaybe_240a10(struct E240a10 *q, s32 kind)
{
    struct Root240a10 *g;
    void *a;
    void *b;
    class Obj240a10 *o;

    if (kind != 2) {
        return 0;
    }
    g = GetGameData_1fede0();
    a = ScriptGetInt_2490f0(q++);
    o = CharaMgrPoolFindById_3a8c60(g->m14, a);
    if (o == 0) {
        return 0;
    }
    b = ScriptGetInt_2490f0(q);
    o->call(b != 0);
    return 1;
}
