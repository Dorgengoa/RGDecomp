#include "types.h"
#include "vec.h"

/* Member of the 5-clone group headed by EffectParamRandomizeApplyRgba_198ae0 (400 B each).
   This member differs from the head in the component count (4 vs 3), the
   source row `b + K` and the tail setter.  The reading is written up in
   EffectParamRandomizeApplyRgba_198ae0.c. */

typedef struct Jit98 {
    u8   pad00[0x10];
    s32  dist;                  /* +0x10  1 = uniform, 2 = normal */
    s32  link;                  /* +0x14 */
    u8   pad18[0x08];
    Vec4 base;                  /* +0x20 */
    f32  amp[4];                /* +0x30 */
} Jit98;

typedef struct Rng98 {
    s32  m0;
    s32  seed;                  /* +0x04 */
} Rng98;

extern f32  RandFloat_1980f0(s32 *seed);
extern f32  RandGaussian_197d70(s32 *seed);
extern f32  D_0047D420;
extern void CopyQword_18bb60(u128 *dst, const u128 *src);
extern void VecAddThunk_13be20(Vec4 *pd, const Vec4 *pa, const Vec4 *pb);
extern s32  MtxMulPointSwapped_1a8660(void *p4, void *a5, void *a6);

void EffectParamRandomizeApplyPos_199a50(Jit98 *a, Rng98 *b, void *c)
{
    Vec4 out;
    Vec4 w;
    s32 i;

    if (a->dist <= 0) {
        CopyQword_18bb60((u128 *)&out, (const u128 *)&a->base);
    } else {
        VEC4_ZERO(w);
        if (a->dist == 1) {
            for (i = 0; i < 3; i++) {
                (&w.x)[i] = a->amp[i] * (2.0f * (RandFloat_1980f0(&b->seed) - 0.5f));
            }
        } else if (a->dist == 2) {
            for (i = 0; i < 3; i++) {
                (&w.x)[i] = a->amp[i] * (D_0047D420 * RandGaussian_197d70(&b->seed));
            }
        }
        switch (a->link) {
        case 1: w.y = w.x; w.z = w.x; break;
        case 2: w.y = w.x; break;
        case 3: w.z = w.x; break;
        case 4: w.z = w.y; break;
        case 0: break;
        }
        VecAddThunk_13be20(&out, &a->base, &w);
    }
    MtxMulPointSwapped_1a8660(c, (u8 *)b + 0x10, &out);
}
