/* rgp:protos */
#line 1
#include "types.h"

/* CharaVslot48ForwardRelated_1fa9a0 -- shape-identical to merged EffTexUvRandParamApply_19a540 (24 B).
   ONE symbol, TWO entry points: a 4-word virtual tail-call thunk then a
   2-word `return 0` with no symbol of its own.  mwcc gives each function its
   own `.text` and the two sizes SUM to retail's 0x18.
   Vtable slot 0x4C == 4 * (17 + 2), so virtual index 17.
   NOTE: the slot lives in the CLASS, not in a constant -- this file is hand
   derived because a textual immediate substitution would have edited only
   the comment. */

class Vfunc_001FA9A0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" void __attribute__((naked)) CharaVslot48ForwardRelated_1fa9a0(Vfunc_001FA9A0 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *76(%eax)"); 

}

extern "C" s32 func_001FA9A0_e1(void)
{
    return 0;
}
