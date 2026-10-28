/* rgp:protos */
#line 1
#include "types.h"

class VE {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void UnitChildViewCount_3bf1d0(s32);

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_3bf300(VE *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void func_003BF300_e1(s32 p0)
{
    UnitChildViewCount_3bf1d0((p0 + -0x230));
}
