/* rgp:protos */
#line 1
#include "types.h"

/* ONE symbol, 3 entry points.  `lw $25,0x0($4)` / `lw $25,K($25)` /
   `jr $25` is a C++ VIRTUAL tail call: slot K = 4*index + 8.  All the
   entries must come out of ONE translation unit, in listing order --
   mwcc gives each its own .text and the lcf takes them in file order. */

class V3B0930_0 {
public:
    VC_VPTR_MEMBER;
    
    
};

class V3B0930_1 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_3b0930(V3B0930_0 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void __attribute__((naked)) func_003B0930_e1(V3B0930_1 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" s32 func_003B0930_e2(void)
{
    return 0;
}


