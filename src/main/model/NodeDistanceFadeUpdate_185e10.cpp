#include "types.h"

struct Base0 {
    u8 pad000[0x68];
};

class Obj : public Base0 {
public:
    virtual f32 v0();
};

struct ObjRaw {
    u8 pad000[0x3C];
    u32 m3C;
    s32 m40;
    u8 pad044[0x4];
    f32 m48;
    f32 m4C;
    u8 pad050[0x10];
    f32 m60;
};

extern "C" void FadeUpdate_186cd0(u32 *p, f32 t);

extern "C" void NodeDistanceFadeUpdate_185e10(class Obj *o, f32 t)
{
    struct ObjRaw *r;
    f32 v;
    s32 ok;

    r = (struct ObjRaw *)o;
    v = o->v0();
    r->m60 = v;
    if (r->m40 == 0) {
        ok = 1;
    } else if (r->m48 > 0.0f && v > r->m48) {
        ok = 0;
    } else if (r->m4C > 0.0f && v < r->m4C) {
        ok = 0;
    } else {
        ok = 1;
    }
    if (ok == 0) {
        r->m3C = r->m3C | 0x80000000;
    } else {
        r->m3C = r->m3C & 0x7FFFFFFF;
    }
    if (t > 0.0f) {
        FadeUpdate_186cd0(&r->m3C, t);
    }
}
