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

struct C {
    u8 pad000[0x10];
    class C0 *obj;
};

struct B {
    u8 pad000[0x8C];
    struct C *m8C;
};

struct A {
    u8 pad000[0x8];
    struct B *m08;
};

extern "C" s32 RevelationBoardFindById_3eb540(struct A *a, s32 x)
{
    struct B *p;

    p = a->m08;
    if (p != 0) {
        return p->m8C->obj->v26(x);
    }
    return 0;
}
