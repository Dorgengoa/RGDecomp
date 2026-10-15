#include "types.h"

struct VtableObj {
    virtual void v0() {}
    virtual void v1() {}
    virtual void v2() {}
    virtual void v3() {}
    virtual void v4() {}
    virtual void v5() {}
    virtual void v6() {}
    virtual void v7() {}
    virtual void v8() {}
    virtual void v9() {}
    virtual void v10() {}
    virtual void v11() {}
    virtual void v12() {}
    virtual void v13() {}
    virtual void v14() {}
    virtual void v15() {}
    virtual void v16() {}
    virtual void v17() {}
    virtual void v18() {}
    virtual void v19() {}
    virtual void v20() {}
    virtual void v21() {}
    virtual void v22() {}
    virtual void v23() {}
    virtual void v24() {}
    virtual void v25() {}
    virtual s32 v26(s16 arg);
};

struct Inner {
    u8 pad00[0x10];
    VtableObj *unk10;
};

struct Outer {
    u8 pad00[0x70];
    Inner *unk70;
};

extern "C" Outer *D_004837C4;
extern "C" s32 BattleEncounterStart_3a41f0(s32, s32, s32);

extern "C" s32 BattleEncounterStartById_3a4160(s32 arg0, s64 arg1, s32 arg2)
{
    Inner *inner;
    VtableObj *this2;
    s32 temp_2;

    if (arg1 < 0) {
        return 0;
    }
    if (D_004837C4 == 0) {
        return 0;
    }
    inner = D_004837C4->unk70;
    this2 = inner->unk10;
    temp_2 = this2->v26((s16)arg1);
    if (temp_2 != 0) {
        return BattleEncounterStart_3a41f0(arg0, temp_2, arg2);
    }
    return 0;
}
