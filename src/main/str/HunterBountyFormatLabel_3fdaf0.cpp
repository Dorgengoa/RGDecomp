/* MATCH (s41a5): the vtable call is a real C++ virtual (vptr 0, slot 0x70 =
   index 26) taking an s16; the three guards are early returns.  The old
   2-bad $a3-before-$a1 residue was Sprintf_1343b8's LAST parameter type: it
   is `s32`, not `s16` -- declared s16, mwcc re-narrowed the argument and
   scheduled it after $a1. */
#include "types.h"

class VE3FD {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void * v26(s16);
};

extern "C" s32 Sprintf_1343b8(s8 *, s32, s32, s32);
extern "C" void *D_00483B28;

extern "C" s32 HunterBountyFormatLabel_3fdaf0(void *arg0, s8 *arg1)
{
    VE3FD *self;
    void *temp_2;

    if (arg1 == NULL) {
        return 0;
    }
    *arg1 = 0;
    if (D_00483B28 == NULL) {
        return 0;
    }
    self = *(VE3FD **)((u8 *)(*(void **)((u8 *)(*(void **)((u8 *)D_00483B28 + 0x8)) + 0x64)) + 0xC);
    temp_2 = self->v26(*(s16 *)((u8 *)arg0 + 0x8));
    if (temp_2 == NULL) {
        return 0;
    }
    Sprintf_1343b8(arg1, *(s32 *)((u8 *)arg0 + 0x4), *(s32 *)((u8 *)temp_2 + 0x4), *(s16 *)((u8 *)arg0 + 0xE));
    return 1;
}
