#include "types.h"

class Base186FC0 { public: u8 pad000[0x68]; };
class V186FC0 : public Base186FC0 {
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
    virtual void v10(s32 a, s32 b);
};

extern "C" s32 FadeIsVisible_186de0(void *a);

extern "C" void MapAreaModelDrawPass0_186fc0(V186FC0 *o)
{
    o->v10(0, 0);
}

extern "C" void func_00186FC0_e1(V186FC0 *o)
{
    o->v10(1, 0);
}

extern "C" s32 func_00186FC0_e2(V186FC0 *o)
{
    if (*(s16 *)((u8 *)o + 0x32) != 0) {
        return FadeIsVisible_186de0((u8 *)o + 0x3C);
    }
    return 0;
}
