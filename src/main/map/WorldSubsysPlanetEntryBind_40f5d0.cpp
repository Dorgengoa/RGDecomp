#include "types.h"

class A {
public:
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5(void *a, void *b, void *c);
};

struct ARaw {
    u8 pad000[0x10];
    void *m10;
    u8 pad014[0x80];
    void *m94;
};

struct X {
    u8 pad00[0xC];
    void *m0C;
};

struct B {
    struct X *m00;
    u8 pad04[0x10];
    void *m14;
};

extern void *D_004800E8 __attribute__((section(".sdata")));
extern "C" void Sprintf_1343b8(char *buf, void *fmt, void *a, void *b);

extern "C" s32 WorldSubsysPlanetEntryBind_40f5d0(class A *a, struct B *b, void *c)
{
    char buf[0x80];
    struct X *x;
    void *y;
    void *g;
    s32 r;
    struct ARaw *ar;

    ar = (struct ARaw *)a;
    if (ar->m10 == 0 || b == 0) {
        return 0;
    }
    x = b->m00;
    if (x == 0) {
        return 0;
    }
    if (b->m14 == 0) {
        return 0;
    }
    y = x->m0C;
    if (y == 0) {
        return 0;
    }
    g = D_004800E8;
    if (g == 0) {
        return 0;
    }
    Sprintf_1343b8(buf, g, y, y);
    ar->m94 = 0;
    r = a->v5(b->m14, c, buf) & 0xFF;
    if (r) {
        ar->m94 = b;
    }
    return r;
}
