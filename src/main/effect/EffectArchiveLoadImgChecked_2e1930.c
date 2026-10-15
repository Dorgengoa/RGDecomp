#include "types.h"

typedef struct R {
    s16 a;
    s32 b;
    s32 c;
    s32 d;
} R;

typedef struct RV {
    s16 a;
    s32 b;
    volatile s32 c;
    s32 d;
} RV;

typedef struct P {
    u8 pad000[0x1674];
    u8 m1674;
} P;

extern R EffectArchiveLoadImg_2defe0(u8 *p, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                      s32 a8, s32 a9);

void EffectArchiveLoadImgChecked_2e1930(R *out, P *p, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                  s32 a7, s32 a8, s32 a9)
{
    RV r;
    R  t;
    s32 c;
    s32 b;
    s32 d;

    if (a4 == 0) {
        out->a = 2;
        out->b = -1;
        out->c = 0;
        out->d = r.d;
        return;
    }
    if (a5 == 0) {
        out->a = 2;
        out->b = -1;
        out->c = 0;
        out->d = r.d;
        return;
    }
    if (a6 == 0) {
        out->a = 2;
        out->b = -1;
        out->c = 0;
        out->d = r.d;
        return;
    }
    if (a7 == 0) {
        out->a = 2;
        out->b = -1;
        out->c = 0;
        out->d = r.d;
        return;
    }
    if (a8 == 0) {
        out->a = 2;
        out->b = -1;
        out->c = 0;
        out->d = r.d;
        return;
    }

    t = EffectArchiveLoadImg_2defe0(&p->m1674, a2, a3, a4, a5, a6, a7, a8, a9);
    b = t.b;
    d = t.d;
    out->a = t.a;
    out->b = b;
    c = t.c;
    r.c = c;
    out->c = c;
    out->d = d;
}
