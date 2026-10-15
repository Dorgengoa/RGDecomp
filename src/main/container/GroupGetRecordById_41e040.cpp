#include "types.h"

struct VTableObj0041e040 {
    virtual s32 v0() { return 0; }
    virtual s32 v1() { return 0; }
    virtual s32 v2() { return 0; }
    virtual s32 v3() { return 0; }
    virtual s32 v4() { return 0; }
    virtual s32 v5() { return 0; }
    virtual s32 v6() { return 0; }
    virtual s32 v7() { return 0; }
    virtual s32 v8() { return 0; }
    virtual s32 v9() { return 0; }
    virtual s32 v10() { return 0; }
    virtual s32 v11() { return 0; }
    virtual s32 v12() { return 0; }
    virtual s32 v13() { return 0; }
    virtual s32 v14() { return 0; }
    virtual s32 v15() { return 0; }
    virtual s32 v16() { return 0; }
    virtual s32 v17() { return 0; }
    virtual s32 v18() { return 0; }
    virtual s32 v19() { return 0; }
    virtual s32 v20() { return 0; }
    virtual s32 v21() { return 0; }
    virtual s32 v22() { return 0; }
    virtual s32 v23() { return 0; }
    virtual s32 v24() { return 0; }
    virtual s32 v25() { return 0; }
    virtual s32 v26(s16 arg1);
};

extern "C" VTableObj0041e040 *GroupFindByKey_41e090(void);

extern "C" s32 GroupGetRecordById_41e040(s32 unused0, s32 unused1, s64 arg2)
{
    VTableObj0041e040 *self;
    s16 v;

    self = GroupFindByKey_41e090();
    if (self != NULL) {
        v = (s16)arg2;
        return self->v26(v);
    }
    return 0;
}
