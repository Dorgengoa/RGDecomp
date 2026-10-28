/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x004F7A80 -- inlined destructor chain.  The two `sw` are vptr
 * writes done through an alias struct with `volatile` members (mwcc
 * dead-stores otherwise; a real C++ dtor would emit OUR vtable into this
 * object's .rodata, a link blocker).  `lw $25,0xF0($16) / lw $25,0x10($25)
 * / jalr $25 ; addiu $4,$16,0x10` is a virtual call on the EMBEDDED
 * sub-object at +0x10 whose own vptr sits at +0xE0.
 * [[jalr-is-cpp-virtual]] */

class VS {
public:
    u8 pad000[0xE0];
    VC_VPTR_MEMBER; 
    void s02(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }               /* slot 0x10 */
};

struct RawObj {
    u8 pad000[0xF0];
    const void *volatile vptr0F0;
    u8 pad0F4[0x1B0 - 0xF4];
    const void *volatile vptr1B0;
};

extern "C" u8 D_0046FFA0[];
extern "C" u8 D_0046FFC0[];

extern "C" void *insect_ModelCtor_4f7a80(void *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    ((RawObj *)o)->vptr1B0 = D_0046FFC0;
    ((RawObj *)o)->vptr0F0 = D_0046FFA0;
    ((VS *)((s32)o + 0x10))->s02((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    return o;
}
