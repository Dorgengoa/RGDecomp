/* rgp:protos */
#define RGP_SELF_factory_FactoryRectFrameEdge_50a180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0050A180 -- draw the conveyor belt run between two
 * points as `n' unit quads: build the segment matrix, then per step transform
 * the four corner points of the template and emit one sprite.  820 bytes.
 */

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct Mtx4 {
    Vec4 v[4];
} Mtx4;

typedef union W {
    f32 f;
    s32 i;
} W;



typedef struct Pt2 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
} Pt2;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_00480E60;
extern f32 D_00480E64;
extern f32 D_00480E68;
extern f32 D_00480E6C;
extern s32 factory_D_0050C930[16];

void factory_FactoryRectFrameEdge_50a180(s32 unused, s32 g, s32 col, s32 row, s32 pal,
                          f32 sc, f32 x0, f32 y0, f32 x1, f32 y1, f32 z)
{
    Mtx4 m __attribute__((aligned(16)));
    volatile W rc[4] __attribute__((aligned(16)));
    f32  pts[16] __attribute__((aligned(16)));
    Vec4 tp[4] __attribute__((aligned(16)));
    Pt2  op[4] __attribute__((aligned(16)));
    s32  i;
    s32  n;
    s32  ty;
    s32  by;
    s32  bx;
    const s32 *sp;
    s32  *dp;
    s32  k;

    MatIdentity_1cbe40(&m);
    m.v[2].x = x1 - x0;
    m.v[2].y = 0.0f;
    m.v[2].z = y1 - y0;
    m.v[2].w = 0.0f;
    VecCross_1cb9f0(&m, &m.v[1], &m.v[2]);
    m.v[3].x = x0;
    m.v[3].y = z;
    m.v[3].z = y0;
    m.v[3].w = 1.0f;
    n = (s32)Floorf_128e30(0.5f + ((0.5f * VecLength_1cb4c0(&m.v[2])) / sc));
    if (n <= 0) {
        return;
    }
    VecDivScalar_1cbbf0(&m.v[2], &m.v[2], (f32)n);
    VecScaleToLength_1cb510(&m, &m, sc);
    i = 0;
    ty = row * 0x18;
    *(Vec4 *)rc = *(Vec4 *)&D_00480E60;
    by = (ty + rc[3].i) - 1;
    bx = (rc[0].i + rc[2].i) - 1;
    while (i < n) {
        sp = factory_D_0050C930;
        dp = (s32 *)pts;
        k = 8;
        do {
            dp[0] = sp[0];
            dp[1] = sp[1];
            sp += 2;
            dp += 2;
            k--;
        } while (k > 0);
        pts[2] = (f32)i;
        pts[6] = (f32)i;
        pts[10] = (f32)(i + 1);
        pts[14] = (f32)(i + 1);
        MatMulPoint_1cb8e0(&tp[0], &m, (Vec4 *)&pts[0]);
        MatMulPoint_1cb8e0(&tp[1], &m, (Vec4 *)&pts[4]);
        MatMulPoint_1cb8e0(&tp[2], &m, (Vec4 *)&pts[8]);
        MatMulPoint_1cb8e0(&tp[3], &m, (Vec4 *)&pts[12]);
        if (ProjectToScreen_15d340(&op[0], &tp[0]) != 0) {
            if (ProjectToScreen_15d340(&op[1], &tp[1]) != 0) {
                if (ProjectToScreen_15d340(&op[2], &tp[2]) != 0) {
                    if (ProjectToScreen_15d340(&op[3], &tp[3]) != 0) {
                        GsPktOpenPrim_13f730(g, 4);
                        GsPktSetRGBAQVec_13edd0(g, pal);
                        GsPktSetTexture_13ec00(g, col);
                        GsPktSetUV_13ed60(g, rc[0].i, ty);
                        GsPktSetXYZVecI_13eeb0(g, &op[0]);
                        GsPktSetUV_13ed60(g, rc[0].i, by);
                        GsPktSetXYZVecI_13eeb0(g, &op[1]);
                        GsPktSetUV_13ed60(g, bx, ty);
                        GsPktSetXYZVecI_13eeb0(g, &op[2]);
                        GsPktSetUV_13ed60(g, bx, by);
                        GsPktSetXYZVecI_13eeb0(g, &op[3]);
                        GsPktClose_13f5b0(g);
                    }
                }
            }
        }
        i++;
    }
}
