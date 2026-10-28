/* SPDX-License-Identifier: CC0-1.0 */
/* The game's only VU0 microprogram as native C (docs/NATIVE-CPU.md "vcallms").
 *
 * `vcallms 0x0` (MatFromSRTVu0_13bc90, MatRotateVu0_13bc20) runs the program
 * GfxSysInit uploads with the VIF0 chain D_00445810 (micro address 0x000,
 * 112 pairs; disassembly: rg-vucensus --dis).  In: vf1 = scale, vf2 = Euler
 * angles, vf3 = translation.  Out: vf4..vf7 = the rows of
 *     diag(s) * Rx(r.x) * Ry(r.y) * Rz(r.z),  row 3 = (t.xyz, 1).
 *
 * Program structure (micro addresses):
 *   0x000-0x030  vf4/5/6 = diag(s), vf7 = (t.xyz, 1)
 *   0x038        addx.xyz vf00, vf02, vf00x: sets the MAC zero flags of the
 *                angles (the write to vf00 is dropped); FMAND/IBEQ then pick
 *                0x378 (all zero: done), 0x218 (x = y = 0: z only), else
 *                vi03 = Zz and fall through
 *   0x088-0x210  sin/cos of (ax - pi/2, ax, ay - pi/2, ay) in four lanes (the
 *                range reduction adds and subtracts 1.5 * 2^23, which relies
 *                on round-toward-zero), then rows *= Rx * Ry
 *   0x218        z == 0: done; else 0x228-0x370 the same for (az - pi/2, az)
 *                and rows *= Rz.
 * Every FMAC operation below is the program's, in program order, on the same
 * lanes, with the I register value each pair sees (an I-bit pair loads I for
 * the NEXT pair's upper instruction).  With VU float semantics
 * (port/vu0.h without RG_VU0_IEEE) the result is bit-exact against the
 * interpreter running the retail program (ctest vu0native.srt); with
 * RG_VU0_IEEE it is the same algorithm in IEEE single. */
#include "port/vu0.h"

typedef rg_vu_u32 u32;
typedef rg_vf V;

#define ADD rg_vu_addf
#define SUB rg_vu_subf
#define MUL rg_vu_mulf

static const V vf0 = {.u = {0, 0, 0, 0x3F800000u}};

static inline V bc(V v, int lane)
{
    V r;
    r.u[0] = r.u[1] = r.u[2] = r.u[3] = v.u[lane];
    return r;
}

static inline V sc(u32 x)
{
    V r;
    r.u[0] = r.u[1] = r.u[2] = r.u[3] = x;
    return r;
}

/* d.mask = s op t */
static inline void vadd(V *d, int m, V s, V t)
{
    int k;
    for (k = 0; k < 4; k++)
        if (m & (1 << k))
            d->u[k] = ADD(s.u[k], t.u[k]);
}
static inline void vsub(V *d, int m, V s, V t)
{
    int k;
    for (k = 0; k < 4; k++)
        if (m & (1 << k))
            d->u[k] = SUB(s.u[k], t.u[k]);
}
static inline void vmul(V *d, int m, V s, V t)
{
    int k;
    for (k = 0; k < 4; k++)
        if (m & (1 << k))
            d->u[k] = MUL(s.u[k], t.u[k]);
}
/* madd/msub: d = acc +- s*t (product rounded first) */
static inline void vmadd(V *d, int m, V acc, V s, V t)
{
    int k;
    for (k = 0; k < 4; k++)
        if (m & (1 << k))
            d->u[k] = ADD(acc.u[k], MUL(s.u[k], t.u[k]));
}
static inline void vmsub(V *d, int m, V acc, V s, V t)
{
    int k;
    for (k = 0; k < 4; k++)
        if (m & (1 << k))
            d->u[k] = SUB(acc.u[k], MUL(s.u[k], t.u[k]));
}
static inline void vabs(V *d, int m, V s)
{
    int k;
    for (k = 0; k < 4; k++)
        if (m & (1 << k))
            d->u[k] = s.u[k] & 0x7FFFFFFFu;
}
static inline void vmax(V *d, int m, V s, V t)
{
    int k;
    for (k = 0; k < 4; k++)
        if (m & (1 << k))
            d->u[k] = rg_vu_maxf(s.u[k], t.u[k]);
}

/* acc - 1.5*2^23 + 1.5*2^23 on acc = -|a|/(2 pi) <= 0: with the VU's
 * round-toward-zero adds this is -floor(|a|/(2 pi)) = ceil(acc), the integer
 * part of the range reduction.  IEEE round-to-nearest would give round()
 * instead and break the reduction, so the native float form says ceil. */
static inline void reduce_int(V *acc, int m, V one)
{
#ifdef RG_VU0_IEEE
    int k;
    (void)one;
    for (k = 0; k < 4; k++)
        if (m & (1 << k))
            acc->f[k] = __builtin_ceilf(acc->f[k]);
#else
    vmsub(acc, m, *acc, one, sc(0x4B400000u)); /* msubai acc, vf11, I (1.5*2^23) */
    vmadd(acc, m, *acc, one, sc(0x4B400000u)); /* maddai acc, vf11, I */
#endif
}

/* the program's constants (LOI immediates) */
#define K_HALF_PI   0x3FC90FD8u /* 1.5707963 (one ulp under pi/2) */
#define K_M1_2PI    0xBE22F987u /* -1/(2 pi) */
#define K_0_5       0x3F000000u
#define K_0_25      0x3E800000u
#define K_C9        0xC2992661u /* -76.575 */
#define K_C7        0xC2255DE0u /* -41.3417 */
#define K_C5        0x42A33457u /* 81.6022 */
#define K_C3        0x421ED7B7u /* 39.7107 */
#define K_2PI       0x40C90FDAu /* 6.2831855 */

enum { X = 1, Y = 2, Z = 4, W = 8, XY = 3, XZ = 5, YW = 10, XZW = 13, ZW = 12,
       XYW = 11, YZW = 14, XYZ = 7, XYZW = 15 };

/* rows *= R, R in (vf12, vf11, vf10) as the program builds it:
   row' = vf12 * row.x + vf11 * row.y + vf10 * row.z */
static inline void apply_rows(V *v4, V *v5, V *v6, V v10, V v11, V v12)
{
    V acc;
    acc = vf0; /* fully written by the mula */
    vmul(&acc, XYZW, v12, bc(*v4, 0));
    vmadd(&acc, XYZW, acc, v11, bc(*v4, 1));
    vmadd(v4, XYZW, acc, v10, bc(*v4, 2));
    vmul(&acc, XYZW, v12, bc(*v5, 0));
    vmadd(&acc, XYZW, acc, v11, bc(*v5, 1));
    vmadd(v5, XYZW, acc, v10, bc(*v5, 2));
    vmul(&acc, XYZW, v12, bc(*v6, 0));
    vmadd(&acc, XYZW, acc, v11, bc(*v6, 1));
    vmadd(v6, XYZW, acc, v10, bc(*v6, 2));
}

void rg_vu0_srt(rg_vf out[4], const rg_vf *s, const rg_vf *r, const rg_vf *t)
{
    V v1 = *s, v2 = *r, v3 = *t;
    V v4 = vf0, v5 = vf0, v6 = vf0, v7 = vf0;
    V v10 = vf0, v11 = vf0, v12 = vf0, v13 = vf0, v14 = vf0, v15 = vf0, v16 = vf0, acc = vf0;
    int zx, zy, zz;

    vmul(&v4, YZW, vf0, bc(vf0, 0));                /* 0x000 mulx.yzw vf4, vf0, vf0x */
    v7.u[3] = vf0.u[3];                             /*       move.w vf7, vf0 */
    vmul(&v5, XZW, vf0, bc(vf0, 0));                /* 0x008 */
    vmul(&v6, XYW, vf0, bc(vf0, 0));                /* 0x010 */
    vadd(&v7, XYZ, vf0, v3);                        /* 0x018 add.xyz vf7, vf0, vf3 */
    vadd(&v4, X, vf0, bc(v1, 0));                   /* 0x020 addx.x vf4, vf0, vf1x */
    vadd(&v5, Y, vf0, bc(v1, 1));                   /* 0x028 */
    vadd(&v6, Z, vf0, bc(v1, 2));                   /* 0x030 */
    /* 0x038 addx.xyz vf00, vf02, vf00x: MAC Z flag per lane = (vf2 + 0) == 0 */
    zx = (ADD(v2.u[0], 0) & 0x7FFFFFFFu) == 0;
    zy = (ADD(v2.u[1], 0) & 0x7FFFFFFFu) == 0;
    zz = (ADD(v2.u[2], 0) & 0x7FFFFFFFu) == 0;
    if (zx && zy && zz)
        goto done;                                  /* 0x060 ibeq -> 0x378 */
    if (!(zx && zy)) {
        /* ---- 0x088: Rx * Ry, lanes (ax - pi/2, ax, ay - pi/2, ay) */
        vadd(&v11, X, vf0, bc(v2, 0));              /* 0x088 addx.x vf11, vf0, vf2x */
        vadd(&v11, Z, vf0, bc(v2, 1));              /* 0x090 addy.z vf11, vf0, vf2y */
        vadd(&v11, Y, vf0, bc(v11, 0));             /* 0x098 addx.y vf11, vf0, vf11x */
        vmul(&v11, W, vf0, bc(v11, 2));             /* 0x0A0 mulz.w vf11, vf0, vf11z  (I = pi/2) */
        vsub(&v11, XZ, v11, sc(K_HALF_PI));         /* 0x0A8 subi.xz            (I = -1/2pi) */
        vabs(&v10, XYZW, v11);                      /* 0x0B0 */
        vmax(&v11, XYZW, vf0, bc(vf0, 3));          /* 0x0B8 maxw vf11 = 1 */
        vmul(&acc, XYZW, v10, sc(K_M1_2PI));        /* 0x0C0 mulai          (I = 1.5*2^23) */
        reduce_int(&acc, XYZW, v11);                /* 0x0C8 msubai, 0x0D0 maddai (I = -1/2pi) */
        vmsub(&acc, XYZW, acc, v10, sc(K_M1_2PI));  /* 0x0D8 msubai         (I = 0.5) */
        vmsub(&v11, XYZW, acc, v11, sc(K_0_5));     /* 0x0E0 msubi          (I = 0.25) */
        vabs(&v11, XYZW, v11);                      /* 0x0E8 */
        vsub(&v11, XYZW, v11, sc(K_0_25));          /* 0x0F0 subi */
        vmul(&v10, YW, vf0, bc(vf0, 0));            /* 0x0F8 mulx.yw vf10 = 0 */
        vmul(&v14, XYZW, v11, v11);                 /* 0x100                (I = c9) */
        vmul(&v16, XYZW, v11, sc(K_C9));            /* 0x108 muli           (I = c7) */
        vmul(&v15, XYZW, v11, sc(K_C7));            /* 0x110 muli           (I = c5) */
        vmul(&v12, XYZW, v11, sc(K_C5));            /* 0x118 muli */
        vmul(&v13, XYZW, v14, v14);                 /* 0x120 */
        vmul(&v16, XYZW, v16, v14);                 /* 0x128 */
        vmul(&acc, XYZW, v15, v14);                 /* 0x130 mula           (I = c3) */
        vmul(&v14, XYZW, v11, sc(K_C3));            /* 0x138 muli */
        vmul(&v15, XYZW, v13, v13);                 /* 0x140 */
        vmadd(&acc, XYZW, acc, v16, v13);           /* 0x148 madda */
        vmadd(&acc, XYZW, acc, v12, v13);           /* 0x150 madda          (I = 2pi) */
        vmadd(&acc, XYZW, acc, v11, sc(K_2PI));     /* 0x158 maddai */
        vmadd(&v13, XYZW, acc, v14, v15);           /* 0x160 madd vf13 */
        vadd(&v11, Y, vf0, bc(vf0, 3));             /* 0x168 addw.y vf11 = 1 */
        vmul(&v11, XZW, vf0, bc(vf0, 0));           /* 0x170 */
        vmul(&v12, YW, vf0, bc(vf0, 0));            /* 0x178 */
        vadd(&v12, X, vf0, bc(v13, 3));             /* 0x180 addw.x vf12, vf0, vf13w */
        vsub(&v12, Z, vf0, bc(v13, 2));             /* 0x188 subz.z vf12, vf0, vf13z */
        vadd(&v10, Z, vf0, bc(v13, 3));             /* 0x190 addw.z vf10, vf0, vf13w */
        vadd(&v10, X, vf0, bc(v13, 2));             /* 0x198 addz.x vf10, vf0, vf13z */
        vmul(&v13, Z, v6, bc(v13, 0));              /* 0x1A0 mulx.z vf13, vf6, vf13x */
        vmul(&acc, XYZW, v12, bc(v4, 0));           /* 0x1A8 mulax acc, vf12, vf4x */
        vmul(&v14, Y, v5, bc(v13, 0));              /* 0x1B0 mulx.y vf14, vf5, vf13x */
        vmul(&v5, Y, v5, bc(v13, 1));               /* 0x1B8 muly.y vf5, vf5, vf13y */
        vsub(&v6, Y, vf0, bc(v13, 2));              /* 0x1C0 subz.y vf6, vf0, vf13z */
        vmadd(&acc, XYZW, acc, v11, bc(v4, 1));     /* 0x1C8 madday */
        vadd(&v5, Z, vf0, bc(v14, 1));              /* 0x1D0 addy.z vf5, vf0, vf14y */
        vmul(&v6, Z, v6, bc(v13, 1));               /* 0x1D8 muly.z vf6, vf6, vf13y */
        vmadd(&v4, XYZW, acc, v10, bc(v4, 2));      /* 0x1E0 maddz vf4 */
        vmul(&acc, XYZW, v12, bc(v5, 0));           /* 0x1E8 */
        vmadd(&acc, XYZW, acc, v11, bc(v5, 1));     /* 0x1F0 */
        vmadd(&v5, XYZW, acc, v10, bc(v5, 2));      /* 0x1F8 */
        vmul(&acc, XYZW, v12, bc(v6, 0));           /* 0x200 */
        vmadd(&acc, XYZW, acc, v11, bc(v6, 1));     /* 0x208 */
        vmadd(&v6, XYZW, acc, v10, bc(v6, 2));      /* 0x210 */
    }
    /* 0x218 ibne vi03, vi00 -> 0x378: vi03 = MAC Zz */
    if (zz)
        goto done;
    /* ---- 0x228: Rz, lanes (az - pi/2, az) */
    vadd(&v11, X, vf0, bc(v2, 2));                  /* 0x228 addz.x vf11, vf0, vf2z */
    vadd(&v11, Y, vf0, bc(v11, 0));                 /* 0x230 addx.y         (I = pi/2) */
    vsub(&v11, X, v11, sc(K_HALF_PI));              /* 0x238 subi.x         (I = -1/2pi) */
    vabs(&v12, XY, v11);                            /* 0x240 */
    vmax(&v11, XY, vf0, bc(vf0, 3));                /* 0x248 */
    vmul(&acc, XY, v12, sc(K_M1_2PI));              /* 0x250 mulai.xy       (I = 1.5*2^23) */
    reduce_int(&acc, XY, v11);                      /* 0x258, 0x260         (I = -1/2pi) */
    vmsub(&acc, XY, acc, v12, sc(K_M1_2PI));        /* 0x268                (I = 0.5) */
    vmsub(&v11, XY, acc, v11, sc(K_0_5));           /* 0x270                (I = 0.25) */
    vabs(&v11, XY, v11);                            /* 0x278 */
    vsub(&v11, XY, v11, sc(K_0_25));                /* 0x280 */
    vmul(&v13, XY, v11, v11);                       /* 0x288                (I = c9) */
    vmul(&v15, XY, v11, sc(K_C9));                  /* 0x290                (I = c7) */
    vmul(&v14, XY, v11, sc(K_C7));                  /* 0x298                (I = c5) */
    vmul(&v12, XY, v11, sc(K_C5));                  /* 0x2A0 */
    vmul(&v10, XY, v13, v13);                       /* 0x2A8 */
    vmul(&v15, XY, v15, v13);                       /* 0x2B0 */
    vmul(&acc, XY, v14, v13);                       /* 0x2B8                (I = c3) */
    vmul(&v13, XY, v11, sc(K_C3));                  /* 0x2C0 */
    vmul(&v14, XY, v10, v10);                       /* 0x2C8 */
    vmadd(&acc, XY, acc, v15, v10);                 /* 0x2D0 */
    vmadd(&acc, XY, acc, v12, v10);                 /* 0x2D8                (I = 2pi) */
    vmadd(&acc, XY, acc, v11, sc(K_2PI));           /* 0x2E0 */
    vmadd(&v11, XY, acc, v13, v14);                 /* 0x2E8 madd.xy vf11 */
    vadd(&v10, Z, vf0, bc(vf0, 3));                 /* 0x2F0 addw.z vf10 = 1 */
    vmul(&v11, ZW, vf0, bc(vf0, 0));                /* 0x2F8 */
    vmul(&v12, ZW, vf0, bc(vf0, 0));                /* 0x300 */
    vadd(&v12, X, vf0, bc(v11, 1));                 /* 0x308 addy.x vf12, vf0, vf11y */
    vadd(&v12, Y, vf0, bc(v11, 0));                 /* 0x310 addx.y vf12, vf0, vf11x */
    vsub(&v11, X, vf0, bc(v11, 0));                 /* 0x318 subx.x vf11, vf0, vf11x */
    vadd(&v11, Y, vf0, bc(v11, 1));                 /* 0x320 addy.y vf11, vf0, vf11y */
    vmul(&v10, XYW, vf0, bc(vf0, 0));               /* 0x328 */
    apply_rows(&v4, &v5, &v6, v10, v11, v12);       /* 0x330-0x370 */
done:
    out[0] = v4;
    out[1] = v5;
    out[2] = v6;
    out[3] = v7;
}
