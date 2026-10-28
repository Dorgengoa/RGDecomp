/* rgp:protos */
#define RGP_SELF_MatDecomposeScaleRotPos_1cad20 1
#define RGP_SELF_RowLength 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vf0_1cad20_t; /* rg:vu0bind vf0 */
#define vf0_1cad20 RG_VU0_BIND_VF(0, rgvb_vf0_1cad20_t)

typedef u128 __attribute__((aligned(4))) rgvb_vf4_1cad20_t; /* rg:vu0bind vf4 */
#define vf4_1cad20 RG_VU0_BIND_VF(4, rgvb_vf4_1cad20_t)


/*rgp*/

/* |row.xyz| */
static inline f32 RowLength(rg_vu0_state *rg_vu0_p_, void *v)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    f32 r;
    vf4_1cad20 = *(u128 *)v;
    vf4_1cad20 = _vmul(vf4_1cad20, 0xE, vf4_1cad20, vf4_1cad20);
    vf4_1cad20 = _vaddbc(vf4_1cad20, 0x8, vf4_1cad20, vf4_1cad20, 4);
    vf4_1cad20 = _vaddbc(vf4_1cad20, 0x8, vf4_1cad20, vf4_1cad20, 2);
    Vu0Length(r, x);
    return r;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* Decompose mtx: scale = row lengths (w = 0), rot via MatToRotPos_1cade0, pos = (row3.xyz, 1). */
void MatDecomposeScaleRotPos_1cad20(f32 *scale, void *rot, void *pos, u8 *mtx)
{ RG_VU0_FRAME;
    u8 tmp[16] __attribute__((aligned(16)));
    scale[0] = RowLength(&rg_vu0, mtx);
    scale[1] = RowLength(&rg_vu0, mtx + 0x10);
    scale[2] = RowLength(&rg_vu0, mtx + 0x20);
    ((s32 *)scale)[3] = 0;
    MatToRotPos_1cade0(rot, tmp, mtx);
    vf4_1cad20 = *(u128 *)(mtx + 0x30);
    vf4_1cad20 = _vmul(vf4_1cad20, 0x1, vf0_1cad20, vf0_1cad20);
    *(u128 *)pos = vf4_1cad20;
}
