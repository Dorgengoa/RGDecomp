/* rgp:protos */
#line 1
#include "types.h"

/* CameraGetEyeThunk_1603e0 -- ONE 52-byte symbol spanning THREE entry points.
 *   0x001603E0  4 w: virtual tail call, vptr at 0xC0, slot 0xA0 (index 38)
 *   0x001603F0  4 w: virtual tail call, vptr at 0xC0, slot 0x9C (index 37)
 *   0x00160400  5 w: tail call VecSub_13be40(b, &a[0x50], &a[0x60])
 */

struct VC0B { unsigned char pad[0xC0]; };
class VC0 : public VC0B {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" void VecSub_13be40(void *, void *, void *);

extern "C" void __attribute__((naked)) CameraGetEyeThunk_1603e0(VC0 *o) { __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 192(%eax), %eax\n\t" "jmp *160(%eax)"); }

extern "C" void __attribute__((naked)) func_001603E0_e1(VC0 *o) { __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 192(%eax), %eax\n\t" "jmp *156(%eax)"); }

extern "C" void func_001603E0_e2(unsigned char *a, void *b)
{
    VecSub_13be40(b, a + 0x50, a + 0x60);
}
