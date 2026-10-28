/* rgp:protos */
#line 1
#include "types.h"

class VE_003FE230 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void DataTableGetCount_3fdf40(s32 p);

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_3fe230(VE_003FE230 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void __attribute__((naked)) func_003FE230_e1(VE_003FE230 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void func_003FE230_e2(s32 p)
{
    DataTableGetCount_3fdf40((p + -0x88));
}
