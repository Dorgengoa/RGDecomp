/* rgp:protos */
#define RGP_SELF_MatToRotPos_1cade0 1
#define RGP_SELF_Vu0CopyVectorW1 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz1cade0_t; /* rg:vu0bind vf0 */
#define vz1cade0 RG_VU0_BIND_VF(0, rgvb_vz1cade0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cade0_t; /* rg:vu0bind vf4 */
#define v4_1cade0 RG_VU0_BIND_VF(4, rgvb_v4_1cade0_t)


static inline void Vu0CopyVectorW1(rg_vu0_state *rg_vu0_p_, void *d, void *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    v4_1cade0 = *(u128 *)s;
    v4_1cade0 = _vmul(v4_1cade0, 0x1, vz1cade0, vz1cade0);
    *(u128 *)d = v4_1cade0;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

typedef struct Rot1cade0 {
    f32 x;
    f32 y;
    f32 z;
    s32 w;
} Rot1cade0;

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1E4;
extern f32 D_0047D1F4;
extern f32 D_0047D1F8;
extern f32 D_0047D1FC;

void MatToRotPos_1cade0(Rot1cade0 *r, u8 *pos, u8 *mtx)
{ RG_VU0_FRAME;
    f32 m[4][4] __attribute__((aligned(16)));

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
    Vu0CopyVectorW1(&rg_vu0, pos, mtx + 0x30);
}
