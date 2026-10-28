/* rgp:protos */
#define RGP_SELF_ScreenFadeBlockWipeOutMaybe_178120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 f0, f4, f8;
    f32 fC;
    s32 f10;
    s32 f14;
    f32 f18;
    s32 f1C, f20, f24;
    f32 f28;
} T_178;

void ScreenFadeBlockWipeOutMaybe_178120(T_178 *p, s32 a, s32 n, f32 v)
{
    p->f20 = a;
    if (p->f10 == 0 || n < 0) {
        p->fC = 0.0f;
    }
    p->f10 = -1;
    p->f14 = 0;
    if (n <= 0) {
        p->f18 = 255.0f;
    } else {
        p->f18 = 128.0f / (f32)n;
    }
    p->f0 = 128.0f;
    p->f4 = 128.0f;
    p->f8 = 128.0f;
    p->f24 = 0;
    p->f1C = 0;
    p->fC = 0.0f;
    p->f24 = 1;
    p->f28 = v;
}
