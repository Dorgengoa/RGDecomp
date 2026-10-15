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
    virtual void s00(); virtual void s01();
    virtual void s02();               /* slot 0x10 */
};

struct RawObj {
    u8 pad000[0xF0];
    const void *volatile vptr0F0;
    u8 pad0F4[0x1B0 - 0xF4];
    const void *volatile vptr1B0;
};

extern "C" u8 D_0046FFA0[];
extern "C" u8 D_0046FFC0[];

extern "C" void *insect_ModelCtor_4f7a80(void *o)
{
    ((RawObj *)o)->vptr1B0 = D_0046FFC0;
    ((RawObj *)o)->vptr0F0 = D_0046FFA0;
    ((VS *)((s32)o + 0x10))->s02();
    return o;
}
