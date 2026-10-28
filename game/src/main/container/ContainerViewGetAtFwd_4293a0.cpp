/* rgp:protos */
#line 1
#include "types.h"

class VE {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void DataTableGetCount_429340(s32);

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_4293a0(VE *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void func_004293A0_e1(s32 p0)
{
    DataTableGetCount_429340((p0 + -0x88));
}
