/* rgp:protos */
#line 1
#include "types.h"

class A {
    u8 pad000[0x1B0];
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
    /* +0x38 */ 
    /* +0x3C */ 
    /* +0x40 */ 
    /* +0x44 */ 
    /* +0x48 */ 
    /* +0x4C */ 
    /* +0x50 */ 
};

extern "C" void __attribute__((naked)) ModelObjReset_1ae2a0(A *self)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 432(%eax), %eax\n\t" "jmp *80(%eax)"); 

}
