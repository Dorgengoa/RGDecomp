#include "types.h"

class C0 {
public:
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
    virtual s32 v13();
    virtual s32 v14();
    virtual s32 v15();
    virtual s32 v16();
    virtual s32 v17();
    virtual s32 v18();
    virtual s32 v19();
    virtual s32 v20();
    virtual s32 v21();
    virtual s32 v22();
    virtual s32 v23();
    virtual s32 v24();
    virtual s32 v25();
    virtual s32 v26(s16 x);
};

extern "C" class C0 *GroupFindByKey_426e10(void *a, s16 b);

extern "C" s32 GroupGetRecordById_426dc0(void *a, s32 b, s32 c)
{
    class C0 *o;

    o = GroupFindByKey_426e10(a, (s16)b);
    if (o != 0) {
        return o->v26((s16)c);
    }
    return 0;
}
