/* rgp:protos */
#define RGP_SELF_EffectArchiveLoadImgChecked_2e1930 1
#define RGP_SELF_EffectArchiveLoadImg_2defe0 1
#include "port/game_protos.h"
#line 1
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

void EffectArchiveLoadImg_2defe0(void *, int, int, int, int, int, void *, void *, void *, int);


void EffectArchiveLoadImgChecked_2e1930(R *out, P *p, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                  s32 a7, s32 a8, s32 a9)
{
    RV r __attribute__((aligned(16)));
    R  t __attribute__((aligned(16)));
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

    t = ({ R rgp_sret; EffectArchiveLoadImg_2defe0((void *)&rgp_sret, (int)(&p->m1674), (int)(a2), (int)(a3), (int)(a4), (int)(a5), (void *)(a6), (void *)(a7), (void *)(a8), (int)(a9)); rgp_sret; });
    b = t.b;
    d = t.d;
    out->a = t.a;
    out->b = b;
    c = t.c;
    r.c = c;
    out->c = c;
    out->d = d;
}
