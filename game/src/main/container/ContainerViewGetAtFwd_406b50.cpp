/* rgp:protos */
#line 1
#include "types.h"

class VE_00406B50 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void DataTableGetCount_406ae0(s32 p);

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_406b50(VE_00406B50 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void __attribute__((naked)) func_00406B50_e1(VE_00406B50 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void func_00406B50_e2(s32 p)
{
    DataTableGetCount_406ae0((p + -0x88));
}
