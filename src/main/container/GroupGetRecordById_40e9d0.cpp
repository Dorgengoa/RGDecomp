#include "types.h"
extern "C" {

extern void **GroupFindByKey_40eaf0(void *, s64);

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
    virtual s32 f(s64 x0);
};
class VC_1 {
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
    virtual s32 f(s64 x0);
};
s32 GroupGetRecordById_40e9d0(void *arg0, s64 arg1, s16 arg2)
{
    void **temp_2;
    void **temp_3;

    temp_3 = *(void ***)((u8 *)arg0 + 0x10);
    if (temp_3 == NULL) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x14) == 0) {
        return 0;
    }
    if (((s64)(arg1 << 0x30) >> 0x30) < 0) {
        return ((VC_0 *)(temp_3))->f(arg2);
    } else {
        temp_2 = GroupFindByKey_40eaf0(arg0, arg1);
        if (temp_2 != NULL) {
            return ((VC_1 *)(temp_2))->f(arg2);
        }
    }
    return 0;
}

}
