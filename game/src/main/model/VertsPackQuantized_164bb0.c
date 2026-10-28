/* rgp:protos */
#define RGP_SELF_Quant 1
#define RGP_SELF_VertsPackQuantized_164bb0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "vec.h"
/* VertsPackQuantized_164bb0 -- pack Vec4s into 3-component 32/16/8-bit vertices (inverse of
 * VertsUnpackQuantized_164d30). 16/8-bit: scale' = 2^15 (2^7) / scale, then VU0 vmul + vftoi0.
 * Asm-free (s88m, was a whole-function asm source): mwcc VU0 intrinsics on
 * `extern` vf15/vf16/vf17 bindings. Stand-ins for the old asm barriers:
 * - the (s32)(u32) launders in Quant keep &s/&t in GPRs (hoisted out of the loop);
 *   Quant's PARAM ORDER (s, v, t) picks t1 = &s, t2 = &t like retail;
 * - volatile qword loads keep lqc2 src-then-scale order;
 * - zero-word block splits on src (after Quant) and d (after i++/src++) keep the
 *   vector op block, then i++/src++, then the lw/store block in retail order. */
#pragma always_inline on

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v15_164bb0_t; /* rg:vu0bind vf15 */
#define v15_164bb0 RG_VU0_BIND_VF(15, rgvb_v15_164bb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v16_164bb0_t; /* rg:vu0bind vf16 */
#define v16_164bb0 RG_VU0_BIND_VF(16, rgvb_v16_164bb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v17_164bb0_t; /* rg:vu0bind vf17 */
#define v17_164bb0 RG_VU0_BIND_VF(17, rgvb_v17_164bb0_t)


static inline void Quant(rg_vu0_state *rg_vu0_p_, Vec4 *s, Vec4 *v, s32 *t)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    if (t) { t = (s32 *)(s32)(u32)t; }
    if (s) { s = (Vec4 *)(s32)(u32)s; }
    v16_164bb0 = *(volatile u128 *)v;
    v17_164bb0 = *(volatile u128 *)s;
    v16_164bb0 = _vmul(v16_164bb0, 0xF, v16_164bb0, v17_164bb0);
    v15_164bb0 = _vftoi0(v15_164bb0, 0xF, v16_164bb0);
    *(u128 *)t = v15_164bb0;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

void VertsPackQuantized_164bb0(void *dst, Vec4 *src, s32 n, s32 bits, Vec4 *scale)
{ RG_VU0_FRAME;
    Vec4 s __attribute__((aligned(16)));
    s32 t[4] __attribute__((aligned(16)));
    s32 i;

    s = *scale;
    if (bits == 32) {
        f32 *d = dst;
        for (i = 0; i < n; ) {
            i++;
            d[0] = src->x;
            d[1] = src->y;
            d[2] = src->z;
            src++;
            d += 3;
        }
    } else if (bits == 16) {
        s16 *d = dst;
        s.x = 32768.0f / scale->x;
        s.y = 32768.0f / scale->y;
        s.z = 32768.0f / scale->z;
        for (i = 0; i < n; ) {
            Quant(&rg_vu0, &s, src, t);
            if (src) { src = (Vec4 *)(s32)(u32)src; }
            i++;
            src++;
            if (d) { d = (void *)(s32)(u32)d; }
            d[0] = t[0];
            d[1] = t[1];
            d[2] = t[2];
            d += 3;
        }
    } else if (bits == 8) {
        s8 *d = dst;
        s.x = 128.0f / scale->x;
        s.y = 128.0f / scale->y;
        s.z = 128.0f / scale->z;
        for (i = 0; i < n; ) {
            Quant(&rg_vu0, &s, src, t);
            if (src) { src = (Vec4 *)(s32)(u32)src; }
            i++;
            src++;
            if (d) { d = (void *)(s32)(u32)d; }
            d[0] = t[0];
            d[1] = t[1];
            d[2] = t[2];
            d += 3;
        }
    }
}
