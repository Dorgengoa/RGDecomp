/* rgp:protos */
#define RGP_SELF_EffectParamRandomizeScl_1995c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Member of the 5-clone group headed by EffectParamRandomizeRgba_198c70 (372 B each).
   This member differs from the head in the component count (4 vs 3) and
   the destination row `b + K`.  The reading is written up in
   EffectParamRandomizeRgba_198c70.c. */

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

/*rgp*/
/*rgp*/
extern f32  D_0047D420;
/*rgp*/
/*rgp*/

void EffectParamRandomizeScl_1995c0(Jit98 *a, Rng98 *b)
{
    Vec4 w __attribute__((aligned(16)));
    s32 i;

    if (a->dist <= 0) {
        CopyQword_18bb60((u128 *)((u8 *)b + 0x30), (const u128 *)&a->base);
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
        VecAddThunk_13be20((Vec4 *)((u8 *)b + 0x30), &a->base, &w);
    }
}
