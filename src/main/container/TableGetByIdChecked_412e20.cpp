#include "types.h"

struct R412E20 { u8 pad000[0x8]; s16 f08; };
struct B412E20 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual struct R412E20 *v26(void *a);
};
struct C412E20 : B412E20 {};

extern "C" struct R412E20 *TableGetByIdChecked_412e20(struct C412E20 *p, s32 k, void *a)
{
    struct R412E20 *r;

    r = p->v26(a);
    if (r == 0) return 0;
    if (r->f08 != (s16)k) return 0;
    return r;
}
