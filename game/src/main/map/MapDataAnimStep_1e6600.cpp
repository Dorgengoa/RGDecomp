/* rgp:protos */
#line 1
#include "types.h"

struct B_001e6600 {
    u8 pad[0x68];
};

struct C_001e6600 : public B_001e6600 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v28(s32 a0) { VCM(void, (void *, s32), 0x78, a0); }
    void v29(f32 a0) { VCM(void, (void *, f32), 0x7C, a0); }
};

struct T_001e6600 {
    u8 pad[0x2C];
    s32 f2C;
};

extern "C" s32 MapDataIsLoadedOrUnloading_1e7980(T_001e6600 *);
extern "C" C_001e6600 *MapDataGetModel_1e7810(T_001e6600 *);

extern "C" void MapDataAnimStep_1e6600(T_001e6600 *p, f32 v)
{
    C_001e6600 *c;

    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(p)) == 0) return;
    p->f2C = p->f2C & ~0x10;
    c = MapDataGetModel_1e7810(p);
    if (c == 0) return;
    c->v28(0);
    c->v29(v);
}
