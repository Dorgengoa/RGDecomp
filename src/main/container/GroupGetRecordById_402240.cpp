#include "types.h"

/* C++ VIRTUAL, twin of GroupGetRecordById_4254b0: vptr +0, slot 0x70 = virtual #26;
   GroupFindByKey_4022b0 takes (arg0, s16). The two guards must be ONE `||` --
   as two separate `if`s the object is 17 bad, and as `&&` + a wrapping
   block it is +2 words. [[levers.d/jalr-is-cpp-virtual]]. */

typedef struct Arg0_402240 {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[4];
    s32 unkC;
} Arg0_402240;

class VE402240 {
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
extern "C" VE402240 *GroupFindByKey_4022b0(Arg0_402240 *, s16);

extern "C" s32 GroupGetRecordById_402240(Arg0_402240 *arg0, s64 arg1, s64 arg2) {
    VE402240 *temp_2;

    if (arg0->unk4 == 0 || arg0->unkC == 0) { return 0; }
    temp_2 = GroupFindByKey_4022b0(arg0, (s16)arg1);
    if (temp_2 != NULL) { return temp_2->v26((s16)arg2); }
    return 0;
}
