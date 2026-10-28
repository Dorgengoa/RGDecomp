/* rgp:protos */
#define RGP_SELF_FrameCalcLocalMatrix_149b40 1
#define RGP_SELF_StoreMatrix 1
#define RGP_SELF_StoreZero 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "vec.h"

#pragma optimization_level 3
#pragma vu0_mmi_reg_binding on
typedef rg_u128 __attribute__((aligned(4))) rgvb_vz149b40_t; /* rg:vu0bind vf0 */
#define vz149b40 RG_VU0_BIND_VF(0, rgvb_vz149b40_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_v1_149b40_t; /* rg:vu0bind vf1 */
#define v1_149b40 RG_VU0_BIND_VF(1, rgvb_v1_149b40_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_v2_149b40_t; /* rg:vu0bind vf2 */
#define v2_149b40 RG_VU0_BIND_VF(2, rgvb_v2_149b40_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_v3_149b40_t; /* rg:vu0bind vf3 */
#define v3_149b40 RG_VU0_BIND_VF(3, rgvb_v3_149b40_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_v4_149b40_t; /* rg:vu0bind vf4 */
#define v4_149b40 RG_VU0_BIND_VF(4, rgvb_v4_149b40_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_va149b40_t; /* rg:vu0bind vf10 */
#define va149b40 RG_VU0_BIND_VF(10, rgvb_va149b40_t)

typedef volatile rg_u128 VQ149b40;
#define SPLIT149b40(p, T) if (p) { p = (T *)(s32)(u32)p; }

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
    s32 *unk18;
    Vec4 *unk1C;
    u8 pad20[0xd];
    s8 unk2D;
    u8 pad2E[0x32];
    Vec4 unk60;
    Vec4 unk70;
    Vec4 unk80;
    Vec4 unk90;
} Obj;

/*rgp*/
/*rgp*/

static inline void StoreMatrix(rg_vu0_state *rg_vu0_p_, void *d0)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    VQ149b40 *d = (VQ149b40 *)(s32)d0;
    SPLIT149b40(d, VQ149b40)
    d[0] = v1_149b40;
    d[1] = v2_149b40;
    d[2] = v3_149b40;
    d[3] = v4_149b40;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline void StoreZero(rg_vu0_state *rg_vu0_p_, void *d0)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    VQ149b40 *d = (VQ149b40 *)(s32)d0;
    SPLIT149b40(d, VQ149b40)
    *d = vz149b40;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

void FrameCalcLocalMatrix_149b40(Obj *self, Mtx4 *out)
{ RG_VU0_FRAME;
    Mtx4 m __attribute__((aligned(16)));
    Vec4 save __attribute__((aligned(16)));
    Vec4 *scale;
    Mtx4 *pm;
    Vec4 *pv;

    scale = self->unk1C;
    if (scale != NULL && self->unk2D == 0) {
        pm = (Mtx4 *)(s32)(u32)&m;
        SPLIT149b40(pm, Mtx4)
        va149b40 = *(VQ149b40 *)scale;
        v1_149b40 = *(VQ149b40 *)&self->unk60;
        v2_149b40 = *(VQ149b40 *)&self->unk70;
        v3_149b40 = *(VQ149b40 *)&self->unk80;
        v4_149b40 = *(VQ149b40 *)&self->unk90;
        SPLIT149b40(pm, Mtx4)
        v1_149b40 = _vmulbc(v1_149b40, 0xF, v1_149b40, va149b40, 8);
        v2_149b40 = _vmulbc(v2_149b40, 0xF, v2_149b40, va149b40, 4);
        v3_149b40 = _vmulbc(v3_149b40, 0xF, v3_149b40, va149b40, 2);
        SPLIT149b40(pm, Mtx4)
        StoreMatrix(&rg_vu0, pm);
    } else {
        m.r[0] = self->unk60;
        m.r[1] = self->unk70;
        m.r[2] = self->unk80;
        m.r[3] = self->unk90;
    }
    if (self->unk18 != NULL && self->unk18[3] != 0) {
        if (self->unk18[3] & 2) {
            MatRotateVu0_13bc20(&m, self->unk18);
            if (self->unk14 != 0) {
                VecAdd_13be20(&m.r[3], &m.r[3], self->unk14);
                m.r[3].w = 1.0f;
            }
        } else {
            *(u128 *)&save = *(u128 *)&m.r[3];
            pv = &m.r[3];
            StoreZero(&rg_vu0, pv);
            MatRotateVu0_13bc20(&m, self->unk18);
            if (self->unk14 != 0) {
                VecAdd_13be20(&m.r[3], &save, self->unk14);
                m.r[3].w = 1.0f;
            } else {
                *(u128 *)&m.r[3] = *(u128 *)&save;
            }
        }
    } else if (self->unk14 != 0) {
        VecAdd_13be20(&m.r[3], &m.r[3], self->unk14);
        m.r[3].w = 1.0f;
    }
    out->r[0] = m.r[0];
    out->r[1] = m.r[1];
    out->r[2] = m.r[2];
    out->r[3] = m.r[3];
}
