#include "types.h"

/* C++ VIRTUAL: `jalr $25` at 0x4254F4 is a virtual call, vptr at +0, slot 0x70
   = virtual #26 (slot = 8 + 4*N). [[levers.d/jalr-is-cpp-virtual]].
   Two more facts were needed on top of the language switch:
   - GroupFindByKey_425640 takes TWO arguments; `$a0` still holds arg0 at the `jal`.
   - the `dsll32/dsra32` pairs are an s16 PARAMETER of the callee, not a cast
     in this function: declaring arg1/arg2 `s16` here removes them (one word
     short each). */

typedef struct S_unk8 S_unk8;
struct S_unk8 {
    u8 pad[8];
    s32 unk8;
};

class VE4254B0 {
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
    virtual s32 v26(s16 a);
};
extern "C" VE4254B0 *GroupFindByKey_425640(S_unk8 *, s16);

extern "C" s32 GroupGetRecordById_4254b0(S_unk8 *arg0, s64 arg1, s64 arg2) {
    VE4254B0 *temp_2;

    if (arg0->unk8 == 0) { return 0; }
    temp_2 = GroupFindByKey_425640(arg0, arg1);
    if (temp_2 != NULL) {
        return temp_2->v26(arg2);
    }
    return 0;
}
