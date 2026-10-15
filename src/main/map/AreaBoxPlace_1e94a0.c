#include "types.h"

typedef struct {
    f32 mn[3];
    f32 mx[3];
    f32 vol;
    f32 h[3];
    f32 c[3];
    f32 m[4];
    f32 up;
    f32 dn;
} Box;

extern void MatRotY_1cb200(f32 *arg0);
extern void MatMulVec4Args_1cb7f0(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
extern void VecCopy_1cbe30(void *arg0, s32 arg1);

void AreaBoxPlace_1e94a0(Box *b, s32 arg1)
{
    u8 v[0x10];
    f32 m[12];
    f32 o[4];
    f32 d;
    f32 e;

    MatRotY_1cb200(m);
    VecCopy_1cbe30(v, arg1);
    d = b->mx[0] - b->mn[0];
    if (d < 0.0f) {
        e = -d;
    } else {
        e = d;
    }
    b->h[0] = 0.5f * e;
    d = b->mx[1] - b->mn[1];
    if (d < 0.0f) {
        e = -d;
    } else {
        e = d;
    }
    b->h[1] = 0.5f * e;
    d = b->mx[2] - b->mn[2];
    if (d < 0.0f) {
        e = -d;
    } else {
        e = d;
    }
    b->h[2] = 0.5f * e;
    b->m[0] = m[0];
    b->m[1] = m[2];
    b->m[2] = m[8];
    b->m[3] = m[10];
    MatMulVec4Args_1cb7f0(o, m, 0.5f * (b->mx[0] + b->mn[0]), 0.5f * (b->mx[1] + b->mn[1]), 0.5f * (b->mx[2] + b->mn[2]), 1.0f);
    b->c[0] = o[0];
    b->c[1] = o[1];
    b->c[2] = o[2];
    b->vol = 8.0f * b->h[0] * b->h[1] * b->h[2];
    b->up = b->c[1] + b->h[1];
    b->dn = b->c[1] - b->h[1];
}
