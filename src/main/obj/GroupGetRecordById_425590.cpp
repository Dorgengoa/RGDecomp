#include "types.h"
extern "C" {
extern s32 GroupEntryMatchesKey_3f41b0(s32, s32);
class VC_0 {
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
    virtual s32 f(s32);
};

s32 GroupGetRecordById_425590(void *self, s16 arg1)
{
    u8 *node;
    s32 i;
    s32 t;
    s32 r;
    if (*(s32 *)((u8 *)self + 0xC) == 0) {
        return 0;
    }
    node = *(u8 **)((u8 *)self + 0x8);
    for (i = 0; i < 2; i++, node += 0x98) {
        t = *(s32 *)(node + 0x94);
        if ((t != 0) && (GroupEntryMatchesKey_3f41b0(t, -1) != 0)) {
            r = ((VC_0 *)node)->f(arg1);
            if (r != 0) {
                return r;
            }
        }
    }
    return 0;
}
}
