/* rgp:protos */
#line 1
#include "types.h"

/* ONE symbol, 2 entry points.  `lw $25,0x0($4)` / `lw $25,K($25)` /
   `jr $25` is a C++ VIRTUAL tail call: slot K = 4*index + 8.  All the
   entries must come out of ONE translation unit, in listing order --
   mwcc gives each its own .text and the lcf takes them in file order. */

struct S39F330 {
    u8    pad000[0xC];
    void *m0C;
};

extern "C" bool EquipSlotSetAbility_3a07b0(void *, void *, long long);
class V39F330_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" void __attribute__((naked)) EquipSlotGetOwnerThunk_39f330(V39F330_0 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *124(%eax)"); 

}

extern "C" s32 func_0039F330_e1(void *a, S39F330 *b, long long rgp_a2)
{
    if (b == 0) return 0;
    return EquipSlotSetAbility_3a07b0(a, b->m0C, (long long)rgp_a2);
}


