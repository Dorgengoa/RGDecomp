#include "types.h"

struct Vec317340 { f32 x; f32 y; f32 z; };

class Base317340 { public: u8 pad000[0xB0]; };
class V317340 : public Base317340 {
public:
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
    virtual void v19(struct Vec317340 *v, f32 x, f32 y, f32 z);
};

extern "C" void AttackObjBaseSetPosVec_317340(V317340 *o, struct Vec317340 *v)
{
    o->v19(v, v->x, v->y, v->z);
}

extern "C" s32 func_00317340_e1(void)
{
    return 1;
}
