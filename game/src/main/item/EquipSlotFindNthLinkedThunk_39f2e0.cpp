/* rgp:protos */
#line 1
#include "types.h"

/* ONE symbol, TWO entries: a 4-word virtual tail-call thunk (vtable slot
   0x80 = declared virtual index 30) then the accessor.  Every token below is
   read off EquipSlotFindNthLinkedThunk_39f2e0.s itself. */

struct G {
    u8    pad00[0x1C];
    void *m1C;
};

struct Self {
    u8   pad00[0xA];
    s16  mA;
};

class V0039F2E0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" G *D_00483748;
extern "C" void *ObjFindById_3bb3a0(void *p, s32 k);

extern "C" void __attribute__((naked)) EquipSlotFindNthLinkedThunk_39f2e0(V0039F2E0 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *128(%eax)"); 

}

extern "C" void *func_0039F2E0_e1(Self *s)
{
    G *g;

    if (s->mA < 0) {
        return 0;
    }
    g = D_00483748;
    if (g != 0) {
        return ObjFindById_3bb3a0(g->m1C, s->mA);
    }
    return 0;
}
