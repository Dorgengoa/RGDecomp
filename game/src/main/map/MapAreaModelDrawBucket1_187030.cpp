/* rgp:protos */
#line 1
#include "types.h"

/* MapAreaModelDrawBucket1_187030 -- 80 B, THREE entries, all virtual tail calls (vptr 0x68).
 *   e0 slot 0x30 (v10) with (0, 1);  e1 same with (0, 2);  e2 slot 0x84 (v31) */

struct VAB { unsigned char pad[0x68]; };
class VA : public VAB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void v10(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x30, a0, a1); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" void MapAreaModelDrawBucket1_187030(VA *o) { o->v10(0, 1); }

extern "C" void func_00187030_e1(VA *o) { o->v10(0, 2); }

extern "C" void __attribute__((naked)) func_00187030_e2(VA *o) { __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 104(%eax), %eax\n\t" "jmp *132(%eax)"); }
