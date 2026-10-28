/* rgp:protos */
#line 1
#include "types.h"

class A {
    u8 pad000[0xC0];
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
    /* +0x54 */ 
    /* +0x58 */ 
    /* +0x5C */ 
    /* +0x60 */ 
    /* +0x64 */ 
    /* +0x68 */ 
    /* +0x6C */ 
    /* +0x70 */ 
    /* +0x74 */ 
    /* +0x78 */ 
    /* +0x7C */ 
    /* +0x80 */ 
    /* +0x84 */ 
    /* +0x88 */ 
    /* +0x8C */ 
    /* +0x90 */ 
    /* +0x94 */ 
    /* +0x98 */ 
    /* +0x9C */ 
    /* +0xA0 */ 
    /* +0xA4 */ 
    /* +0xA8 */ 
    /* +0xAC */ 
    /* +0xB0 */ 
    /* +0xB4 */ 
    /* +0xB8 */ 
};

extern "C" void __attribute__((naked)) CameraGetYawThunk_160460(A *self)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 192(%eax), %eax\n\t" "jmp *184(%eax)"); 

}
