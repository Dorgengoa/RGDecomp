/* rgp:protos */
#line 1
#include "types.h"

class VE_003D5CC0 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_3d5cc0(VE_003D5CC0 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" s32 func_003D5CC0_e1(void)
{
    return 0x30;
}
