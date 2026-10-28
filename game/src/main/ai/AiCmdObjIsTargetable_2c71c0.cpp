/* rgp:protos */
#line 1
#include "types.h"

class V2c7 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 s22C() { return VCM0(u8, 0x22C); }
};

struct A2c7 { u8 pad00[0x1C]; void *m1C; };
struct E2c7 { u8 b[0x8]; };

extern "C" A2c7 * GetGameData_1fede0(void);
extern "C" void *ScriptSlotGetInt_2cc9c0(E2c7 *);
extern "C" V2c7 *ObjFindById_3bb3a0(void *, void *);
extern "C" void ScriptSlotStoreIntRef_2cc900(E2c7 *, u8);

extern "C" s32 AiCmdObjIsTargetable_2c71c0(E2c7 *p)
{
    A2c7 *a;
    void *b;
    V2c7 *c;
    E2c7 *q;
    s32 f;

    q = p;
    a = GetGameData_1fede0();
    b = ScriptSlotGetInt_2cc9c0(q++);
    f = 0;
    c = ObjFindById_3bb3a0(a->m1C, b);
    if (c != 0) {
        f = c->s22C();
    }
    ScriptSlotStoreIntRef_2cc900(q, f);
    return 1;
}
