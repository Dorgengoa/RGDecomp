/* rgp:protos */
#line 1
#include "types.h"

/* ONE symbol, TWO entries: a 4-word virtual tail-call thunk (vtable slot
   0x84 = declared virtual index 31) then the accessor.  Every token below is
   read off EquipSlotFindNthLinkedThunk_39f7f0.s itself. */

struct G {
    u8    pad00[0x14];
    void *m14;
};

struct Self {
    u8   pad00[0xA];
    s16  mA;
};

class V0039F7F0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" G *D_00483748;
extern "C" void *CharaMgrPoolFindById_3a8c60(void *p, s32 k);

extern "C" void __attribute__((naked)) EquipSlotFindNthLinkedThunk_39f7f0(V0039F7F0 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *132(%eax)"); 

}

extern "C" void *func_0039F7F0_e1(Self *s)
{
    G *g;

    if (s->mA < 0) {
        return 0;
    }
    g = D_00483748;
    if (g != 0) {
        return CharaMgrPoolFindById_3a8c60(g->m14, s->mA);
    }
    return 0;
}
