/* rgp:protos */
#line 1
#include "types.h"

/* UnitVslot50ThunkRelated_3b0660 -- shape-identical to merged EffTexUvRandParamApply_19a540 (24 B).
   ONE symbol, TWO entry points: a 4-word virtual tail-call thunk then a
   2-word `return 0` with no symbol of its own.  mwcc gives each function its
   own `.text` and the two sizes SUM to retail's 0x18.
   Vtable slot 0x54 == 4 * (19 + 2), so virtual index 19.
   NOTE: the slot lives in the CLASS, not in a constant -- this file is hand
   derived because a textual immediate substitution would have edited only
   the comment. */

class Vfunc_003B0660 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" void __attribute__((naked)) UnitVslot50ThunkRelated_3b0660(Vfunc_003B0660 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *84(%eax)"); 

}

extern "C" s32 func_003B0660_e1(void)
{
    return 0;
}
