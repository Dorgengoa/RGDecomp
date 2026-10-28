/* rgp:protos */
#line 1
#include "types.h"

class VE {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void DataTableGetCount_408100(s32);

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_408160(VE *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void func_00408160_e1(s32 p0)
{
    DataTableGetCount_408100((p0 + -0x88));
}
