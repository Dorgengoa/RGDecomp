/* rg-override: replaces game/src/main/math/MtxPlaneProjection_13c930.c sha256 842d47c326602927af3090a049602038136359373c2e7d1d945582fd0e6622a4
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern f32 D_0047D7CC;                                  /* -0x79A4(gp) = 0.1 */
extern void VecNormalize_13bd90(void *d, const void *s);

/* Build the 4x4 projection matrix onto the plane through point q (*pq) with
   normal n (*pn.xyz), along direction v (*pv).  When dot(v, q) == 0, q is
   first moved by -0.1 * v. */
void MtxPlaneProjection_13c930(void *out, const void *pn, const void *pq, const void *pv)
{ RG_VU0_FRAME;
    f32 *o = (f32 *)out;
    f32 n[4];                                           /* sp+0x50 */
    f32 q[4];                                           /* sp+0x40 */
    f32 v[4];                                           /* sp+0x30 */
    f32 dot, inv, k, a0, a1, a2, nx, ny, nz, p0, p1, p2, s, r;

    n[0] = ((const f32 *)pn)[0];                        /* lwc1/swc1 0x50.. */
    n[1] = ((const f32 *)pn)[1];
    n[2] = ((const f32 *)pn)[2];
    *(u32 *)&n[3] = 0;                                  /* sw $0, 0x5C($29) */
    __builtin_memcpy(q, pq, 16);                        /* lq $5, 0($6); sq $5, 0x40($29) */
    __builtin_memcpy(v, pv, 16);                        /* lq $2, 0($7); sq $2, 0x30($29) */
    rg_vu0_lqc2(4, v);                                  /* lqc2 vf4, 0($4=sp+0x30) */
    rg_vu0_lqc2(5, q);                                  /* lqc2 vf5, 0($3=sp+0x40) */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 5, 4, 5, RG_BC_NONE);  /* vmul.xyz vf5, vf4, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y);       /* vaddy.x vf5, vf5, vf5y */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z);       /* vaddz.x vf5, vf5, vf5z */
    dot = rg_vu0_getf(5, 0);                            /* qmfc2 $2, vf5; mtc1 $2, $f3 */
    if (0.0f == dot) {                                  /* c.eq.s $f6(0), $f3; bc1fl */
        k = D_0047D7CC;
        /* adda.s $f6(0), q.c; msub.s = ACC - k * v.c */
        q[0] = (0.0f + q[0]) - k * v[0];
        q[1] = (0.0f + q[1]) - k * v[1];
        q[2] = (0.0f + q[2]) - k * v[2];
        rg_vu0_lqc2(4, v);                              /* lqc2 vf4, 0($4) */
        rg_vu0_lqc2(5, q);                              /* lqc2 vf5, 0($3) */
        rg_vu0_fmac(RG_VMUL, RG_XYZ, 5, 4, 5, RG_BC_NONE);
        rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y);
        rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z);
        dot = rg_vu0_getf(5, 0);
    }
    inv = 1.0f / dot;                                   /* div.s $f3, 1.0, $f3 */
    a0 = v[0] * inv;                                    /* $f20 */
    a1 = v[1] * inv;                                    /* $f21 */
    a2 = v[2] * inv;                                    /* $f22 */
    VecNormalize_13bd90(n, n);                          /* jal VecNormalize_13bd90 (sp+0x50, sp+0x50) */
    nx = n[0];                                          /* $f9 */
    ny = n[1];                                          /* $f8 */
    nz = n[2];                                          /* $f0 */
    p0 = a0 * nx;                                       /* $f5 */
    p1 = a1 * ny;                                       /* $f6 */
    p2 = a2 * nz;                                       /* $f4 */
    s = p2 + (p0 + p1);                                 /* add.s $f2, $f5, $f6; add.s $f3, $f4, $f2 */
    r = -1.0f / s;                                      /* div.s $f7, -1.0, $f3 */
    o[0]  = r * (p0 - s);
    o[5]  = r * (p1 - s);
    o[10] = r * (p2 - s);
    o[4]  = r * (a1 * nx);
    o[8]  = r * (a2 * nx);
    o[12] = r * -nx;
    o[1]  = r * (a0 * ny);
    o[9]  = r * (a2 * ny);
    o[13] = r * -ny;
    o[2]  = r * (a0 * nz);
    o[6]  = r * (a1 * nz);
    o[14] = r * -nz;
    *(u32 *)&o[3]  = 0;                                 /* sw $0, 0xC($16) */
    *(u32 *)&o[7]  = 0;                                 /* sw $0, 0x1C($16) */
    *(u32 *)&o[11] = 0;                                 /* sw $0, 0x2C($16) */
    o[15] = r * -s;                                     /* neg.s $f1, $f3; mul.s */
}
