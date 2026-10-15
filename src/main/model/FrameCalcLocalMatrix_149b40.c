#include "types.h"
#include "vec.h"

#pragma optimization_level 3
#pragma vu0_mmi_reg_binding on
extern unsigned __int128 vz149b40 asm("vf0");
extern unsigned __int128 v1_149b40 asm("vf1");
extern unsigned __int128 v2_149b40 asm("vf2");
extern unsigned __int128 v3_149b40 asm("vf3");
extern unsigned __int128 v4_149b40 asm("vf4");
extern unsigned __int128 va149b40 asm("vf10");
typedef volatile unsigned __int128 VQ149b40;
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

extern void MatRotateVu0_13bc20(Mtx4 *, s32 *);
extern void VecAdd_13be20(Vec4 *, Vec4 *, s32);

static inline void StoreMatrix(void *d0)
{
    VQ149b40 *d = (VQ149b40 *)(s32)d0;
    SPLIT149b40(d, VQ149b40)
    d[0] = v1_149b40;
    d[1] = v2_149b40;
    d[2] = v3_149b40;
    d[3] = v4_149b40;
}

static inline void StoreZero(void *d0)
{
    VQ149b40 *d = (VQ149b40 *)(s32)d0;
    SPLIT149b40(d, VQ149b40)
    *d = vz149b40;
}

void FrameCalcLocalMatrix_149b40(Obj *self, Mtx4 *out)
{
    Mtx4 m;
    Vec4 save;
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
        StoreMatrix(pm);
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
            StoreZero(pv);
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
