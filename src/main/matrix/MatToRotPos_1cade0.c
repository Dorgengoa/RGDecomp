#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz1cade0 asm("vf0");
extern u128 v4_1cade0 asm("vf4");

static inline void Vu0CopyVectorW1(void *d, void *s)
{
    v4_1cade0 = *(u128 *)s;
    v4_1cade0 = _vmul(v4_1cade0, 0x1, vz1cade0, vz1cade0);
    *(u128 *)d = v4_1cade0;
}

typedef struct Rot1cade0 {
    f32 x;
    f32 y;
    f32 z;
    s32 w;
} Rot1cade0;

extern void MatOrthonormalizeY_1cb300(f32 m[4][4], u8 *src);
extern f32 Atan2f_1291a8(f32 y, f32 x);
extern f32 Asinf_129190(f32 x);
extern f32 D_0047D1E4;
extern f32 D_0047D1F4;
extern f32 D_0047D1F8;
extern f32 D_0047D1FC;

void MatToRotPos_1cade0(Rot1cade0 *r, u8 *pos, u8 *mtx)
{
    f32 m[4][4];

    MatOrthonormalizeY_1cb300(m, mtx);
    if (m[0][0] == 0.0f && m[0][1] == 0.0f) {
        r->x = 0.0f;
        r->y = (m[0][2] > 0.0f) ? D_0047D1F8 : D_0047D1F4;
        r->z = Atan2f_1291a8(-m[1][0], m[1][1]);
    } else if (m[2][2] < 0.0f) {
        r->x = Atan2f_1291a8(-m[1][2], -m[2][2]);
        r->y = D_0047D1FC - Asinf_129190(-m[0][2]);
        r->z = Atan2f_1291a8(-m[0][1], -m[0][0]);
        if (r->y > D_0047D1FC) {
            r->y -= D_0047D1E4;
        }
    } else {
        r->x = Atan2f_1291a8(m[1][2], m[2][2]);
        r->y = Asinf_129190(-m[0][2]);
        r->z = Atan2f_1291a8(m[0][1], m[0][0]);
    }
    r->w = 0;
    Vu0CopyVectorW1(pos, mtx + 0x30);
}
