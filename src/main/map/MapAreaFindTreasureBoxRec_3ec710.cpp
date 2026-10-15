#include "types.h"

/* PARK, length-correct (35w) 16 bad, was length-short.
   C++ VIRTUAL (vptr +0, slot 0x70 = virtual #26, s16 argument) AND the two
   `arg0->unk8` reads must be STRUCT MEMBERS -- as `(u8 *)arg0 + 8` mwcc CSEs
   the address into a callee-saved register and the object goes length-short.
   Remaining: retail's guard is `bnezl` with the `lh $v1,0x2C($v0)` of the
   result's field duplicated into the annulled slot; hoisting that load to the
   top of the taken arm is +2 words in three spellings. */

struct A3EC710 {
    u8 pad0[8];
    struct { u8 pad0[0x34]; void *unk34; u8 pad38[0x78 - 0x38]; void *unk78; } *unk8;
};

class VE3EC710;
class VE3EC710 {
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
    virtual VE3EC710 * v26(s16 a);
};
extern "C" s32 TreasureBoxRecFind_427b00(s32, s16, s16);

extern "C" s32 MapAreaFindTreasureBoxRec_3ec710(A3EC710 *arg0, s64 arg1, s64 arg2)
{
    s32 temp_4;
    s32 f;
    VE3EC710 *self;
    VE3EC710 *temp_2;

    self = *(VE3EC710 **)((u8 *)arg0->unk8->unk34 + 8);
    temp_2 = self->v26((s16)arg1);
    if (temp_2 == NULL) {
        return 0;
    }
    f = *(s16 *)((u8 *)temp_2 + 0x2C);
    temp_4 = *(s32 *)((u8 *)arg0->unk8->unk78 + 8);
    if (temp_4 != 0) {
        return TreasureBoxRecFind_427b00(temp_4, f, arg2);
    }
    return 0;
}
