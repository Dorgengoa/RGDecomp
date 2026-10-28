/* rgp:protos */
#define RGP_SELF_ScreenFadeBlockFadeOutColor_1782a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 f0, f4, f8;
    s32 fC;
    s32 f10;
    s32 f14;
    f32 f18;
    s32 f1C, f20, f24;
} T_001782a0;

void ScreenFadeBlockFadeOutColor_1782a0(T_001782a0 *p, s32 n, f32 x, f32 y, f32 z)
{
    if (p->f10 == 0 || n < 0) {
        p->fC = 0;
    }
    p->f10 = -1;
    p->f14 = 0;
    if (n <= 0) {
        p->f18 = 255.0f;
    } else {
        p->f18 = 128.0f / (f32)n;
    }
    p->f0 = x;
    p->f4 = y;
    p->f8 = z;
    p->f24 = 0;
    p->f1C = 0;
}
