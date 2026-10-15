#include "types.h"

struct B_0017 {
    u8 pad[0xC0];
};

struct C_0017 : public B_0017 {
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
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35(void *);
    virtual void v36(void *);
};

typedef struct { f32 x, y, z, w; } A_0017;

extern "C" void CameraSetEyeHeight_176da0(C_0017 *p, f32 v)
{
    A_0017 b;
    A_0017 a;

    p->v35(&a);
    p->v36(&b);
    p->v16();
    b.y = a.y + v;
}
