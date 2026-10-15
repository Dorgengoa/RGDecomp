#include "types.h"

typedef struct Cur8 { s32 a, b; } Cur8;

typedef struct T19bc60 {
    u8  pad00[0x2C];
    void *f2C;
} T19bc60;

extern f32 VariantGetFloat_15f740(Cur8 *);
extern char *SlotGetInt_15f720(Cur8 *);
extern void EffObjSetEmitRate_1a97d0(void *, f32, f32, f32, char *);

s32 EffDefCmdEmittPerFrame_19bc60(Cur8 *q, s32 mode, T19bc60 **h)
{
    T19bc60 *t;
    f32 a;
    f32 b;
    f32 c;
    char *s;

    t = *h;
    if (t->f2C == 0) {
        return 0;
    }
    a = VariantGetFloat_15f740(q++);
    b = VariantGetFloat_15f740(q++);
    if (b < 1.0f) {
        b = 1.0f;
    }
    c = 0.0f;
    s = 0;
    if (mode >= 3) {
        s = SlotGetInt_15f720(q++);
    }
    if (mode >= 4) {
        c = VariantGetFloat_15f740(q);
    }
    EffObjSetEmitRate_1a97d0(t->f2C, a, b, c, s);
    return 1;
}
