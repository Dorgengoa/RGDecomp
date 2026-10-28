/* rgp:protos */
#line 1
#include "types.h"

class A {
    u8 pad000[0x4394];
public:
    /* +0x08 */ VC_VPTR_MEMBER;
};

extern "C" void __attribute__((naked)) SceneReset_1c4610(A *self)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 17300(%eax), %eax\n\t" "jmp *8(%eax)"); 

}
