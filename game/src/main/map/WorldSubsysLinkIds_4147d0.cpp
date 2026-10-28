/* rgp:protos */
#line 1
#include "types.h"

class Obj4147d0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * call(void *a) { return VCM(void *, (void *, void *), 0x70, a); }
};

struct It4147d0 {
    u8 b[8];
};

struct E4147d0 {
    u8 pad00[0x4];
    void *m04;
};

struct T4147d0 {
    u8 pad00[0x2C];
    class Obj4147d0 *m2C;
};

struct P4147d0 {
    u8 pad00[0x34];
    struct T4147d0 *m34;
};

extern "C" void IterInit_370170(struct It4147d0 *, void *, int, int);
extern "C" struct E4147d0 *IterNext_370040(struct It4147d0 *it);

extern "C" s32 WorldSubsysLinkIds_4147d0(u8 *p4, struct P4147d0 *p5, int rgp_a2, int rgp_a3)
{
    struct It4147d0 it __attribute__((aligned(16)));
    struct E4147d0 *e;
    u8 *arg;

    if (p5 == 0) {
        return 0;
    }
    arg = p4;
    if (p4 != 0) {
        arg += 0x88;
    }
    IterInit_370170(&it, arg, (int)rgp_a2, (int)rgp_a3);
    while ((e = IterNext_370040(&it)) != 0) {
        e->m04 = p5->m34->m2C->call(e->m04);
    }
    return 1;
}
