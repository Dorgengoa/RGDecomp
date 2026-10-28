/* rgp:protos */
#line 1
#include "types.h"

/* ONE symbol, 2 entry points.  `lw $25,0x0($4)` / `lw $25,K($25)` /
   `jr $25` is a C++ VIRTUAL tail call: slot K = 4*index + 8.  All the
   entries must come out of ONE translation unit, in listing order --
   mwcc gives each its own .text and the lcf takes them in file order. */

class V19A500_0 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void __attribute__((naked)) EffTexAnimeParamApply_19a500(V19A500_0 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void func_0019A500_e1(void)
{
}


