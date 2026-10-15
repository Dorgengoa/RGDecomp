/* PARKED at triage (0 round trips): combines TWO hard patterns -- an
 * ambiguous `(var_7*4)+sp` local-array address (same class as AttackChainMarkersShow_382c40)
 * AND a missing adda.s/madd.s float-accumulator site (ps2-float-accumulator
 * lever) feeding that array's field. Worth a full raw-asm reconstruction in
 * a future session but not inside this throughput pass. Deferred.
 * See asm/matchings/main/RevelationBoardPktSetColorLerp_34ce10.s. */
/* s49m: MATCH */
#include "types.h"

extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);

static inline void clr(void *p, u32 n)
{
    u8 *q;
    u32 c;

    c = n;
    q = (u8 *)p;
    if (q != 0) {
        do {
            *q = 0;
            c--;
            q++;
        } while (c != 0);
    }
}

void RevelationBoardPktSetColorLerp_34ce10(u8 *self, s32 arg1, f32 t, f32 a0, f32 a1, f32 a2, f32 a3,
                  f32 b0, f32 b1, f32 b2, f32 b3)
{
    f32 from[4];
    f32 to[4];
    s32 out[4];
    s32 i;

    clr(from, 16);
    from[0] = a0;
    from[1] = a1;
    from[2] = a2;
    from[3] = a3;
    clr(to, 16);
    to[0] = b0;
    to[1] = b1;
    to[2] = b2;
    to[3] = b3;
    clr(out, 16);
    out[0] = a0;
    out[1] = a1;
    out[2] = a2;
    out[3] = a3;
    if (t > 0.0f) {
        for (i = 0; i < 4; i++) {
            out[i] = from[i] + t * (to[i] - from[i]);
        }
    }
    GsPktSetRGBAQ_13ee40(arg1, out[0], out[1], out[2],
                 (f32)out[3] * *(f32 *)(*(u8 **)(self + 0x77C) + 0xC));
}
