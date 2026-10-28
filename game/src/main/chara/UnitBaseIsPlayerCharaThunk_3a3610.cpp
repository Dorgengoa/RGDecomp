/* rgp:protos */
#line 1
#include "types.h"

/* UnitBaseIsPlayerCharaThunk_3a3610 -- shape-identical to merged EffTexUvRandParamApply_19a540 (24 B).
   ONE symbol, TWO entry points: a 4-word virtual tail-call thunk then a
   2-word `return 0` with no symbol of its own.  mwcc gives each function its
   own `.text` and the two sizes SUM to retail's 0x18.
   Vtable slot 0x44 == 4 * (15 + 2), so virtual index 15.
   NOTE: the slot lives in the CLASS, not in a constant -- this file is hand
   derived because a textual immediate substitution would have edited only
   the comment. */

class Vfunc_003A3610 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" void __attribute__((naked)) UnitBaseIsPlayerCharaThunk_3a3610(Vfunc_003A3610 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *68(%eax)"); 

}

extern "C" s32 func_003A3610_e1(void)
{
    return 0;
}
