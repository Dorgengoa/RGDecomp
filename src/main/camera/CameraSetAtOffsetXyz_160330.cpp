#include "types.h"

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct Base160330 { u8 pad000[0xC0]; };
struct C160330 : Base160330 {
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
    virtual void v30(struct Vec4 *v);
};

extern "C" f32 D_0047DF40;
extern "C" f32 D_0047DF44;
extern "C" f32 D_0047DF48;
extern "C" f32 D_0047DF4C;

extern "C" void CameraSetAtOffsetXyz_160330(struct C160330 *p, f32 x, f32 y, f32 z)
{
    struct Vec4 v;

    v.x = D_0047DF40;
    v.y = D_0047DF44;
    v.z = D_0047DF48;
    v.w = D_0047DF4C;
    v.x = x;
    v.y = y;
    v.z = z;
    p->v30(&v);
}
