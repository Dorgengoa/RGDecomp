#include "types.h"

/* $f0 holds the gp constant only until the jal; after it $f0 is the RETURN
   value of Cosf_128d30, so the second mul is `* r`, not `* K`. */

extern f32 D_0047DB1C;
extern f32 Cosf_128d30(f32 x);

void CharaSquashScaleGet_2191e0(void *p, f32 *out)
{
    f32 t;
    f32 r;
    f32 v;
    f32 u;
    s32 n;

    out[0] = 1.0f;
    out[1] = 1.0f;
    out[2] = 1.0f;
    out[3] = 1.0f;
    n = *(s32 *)((u8 *)p + 4);
    if (n > 0) {
        t = (f32)*(s32 *)((u8 *)p + 8) / (f32)n;
        r = Cosf_128d30(D_0047DB1C * t);
        /* MEASURED: naming the product flips the final mul's rs/rt.
           Source operand order (r * prod) is INERT - same object sha1. */
        u = -(1.0f - t) * *(f32 *)p;
        v = u * r;
        if (v != 0.0f) {
            out[0] = 1.0f - v;
            out[1] = 1.0f + v;
            out[2] = 1.0f - v;
            out[3] = 1.0f;
        }
    }
}
