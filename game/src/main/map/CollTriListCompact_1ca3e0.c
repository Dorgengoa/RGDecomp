/* rgp:protos */
#define RGP_SELF_CollTriListCompact_1ca3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    f32 x, y, z, w;
} FV001ca3e0;

typedef struct {
    s32 w[12];
} B30001ca3e0;

typedef struct {
    s16 h[10];
} H14001ca3e0;

typedef struct {
    B30001ca3e0 a;
    FV001ca3e0 v;
    H14001ca3e0 h;
    s32 unk54;
    u8 pad58[8];
} E001ca3e0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047E280;
extern f32 D_0047E284;
extern f32 D_0047E288;
extern f32 D_0047E28C;
extern f32 D_0047E290;
extern f32 D_0047E294;
extern f32 D_0047E298;
extern f32 D_0047E29C;

s32 CollTriListCompact_1ca3e0(E001ca3e0 *arg0, s32 arg1)
{
    FV001ca3e0 c80 __attribute__((aligned(16)));
    FV001ca3e0 c70 __attribute__((aligned(16)));
    FV001ca3e0 n __attribute__((aligned(16)));
    E001ca3e0 *d;
    E001ca3e0 *s;
    s32 i;

    if (arg0 == NULL || arg1 <= 0) {
        return 0;
    }
    d = arg0;
    s = arg0;
    i = 0;
    { f32 *pa = (f32 *)&c80; pa[0] = D_0047E280; pa[1] = D_0047E284; pa[2] = D_0047E288; pa[3] = D_0047E28C; }
    { f32 *pb = (f32 *)&c70; pb[0] = D_0047E290; pb[1] = D_0047E294; pb[2] = D_0047E298; pb[3] = D_0047E29C; }
    for (; i < arg1; i++, s++) {
        TriNormal_1cb970(&n, s->a.w, &s->a.w[4], &s->a.w[8]);
        if (VecLengthSq_1cb470(&n, 0) < 1.0f) {
            continue;
        }
        if (VecDot3_1cba90(&s->v, &n) < 0.0f) {
            Swap128_1cb4f0((u8 *)s + 0x10, (u8 *)s + 0x20);
            VecNegate_1cb9a0(&n, &n);
        }
        VecNormalize_1cbb80(&s->v, &n);
        VecMin_1cb590(&s->v, &s->v, &c80);
        VecMax_1cb5b0(&s->v, &s->v, &c70);
        d->a = s->a;
        d->v = s->v;
        d->h = s->h;
        d->unk54 = s->unk54;
        d += 1;
    }
    return d - arg0;
}
