/* rgp:protos */
#line 1
#include "types.h"

class A {
public:
    /* +0x08 */ VC_VPTR_MEMBER;
    /* +0x0C */ 
    /* +0x10 */ 
    /* +0x14 */ 
    /* +0x18 */ 
    /* +0x1C */ 
    /* +0x20 */ 
    /* +0x24 */ 
    /* +0x28 */ 
    /* +0x2C */ 
    /* +0x30 */ 
    /* +0x34 */ 
};

extern "C" void __attribute__((naked)) InvObjVirtualReset_3d5120(A *self)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *52(%eax)"); 

}
