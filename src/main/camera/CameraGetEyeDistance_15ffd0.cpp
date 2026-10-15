#include "types.h"

struct Vec4_0015FFD0 {
    f32 x, y, z, w;
};

class VE15FFD0 {
public:
    u8 pad000[0xC0];
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
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void v35(Vec4_0015FFD0 *out);
    virtual void v36(Vec4_0015FFD0 *out);
};
extern "C" f32 VecDistance_13d3d0(const Vec4_0015FFD0 *a, const Vec4_0015FFD0 *b);

extern "C" void CameraGetEyeDistance_15ffd0(VE15FFD0 *self)
{
    Vec4_0015FFD0 b;
    Vec4_0015FFD0 a;

    self->v35(&a);
    a.y = 0.0f;
    self->v36(&b);
    b.y = 0.0f;
    VecDistance_13d3d0(&a, &b);
}
