/* rg-override: replaces game/src/main/camera/FovHorizToVert_13fbe0.c sha256 e0642318fc06637360673db9fb3cd3b51457ef7c25c53e61d339e5b1ba58bf3d
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern f32 D_0047D1FC;                       /* -0x7F74(gp) = pi */
extern f64 Tan_1289b8(f64);                  /* soft-double tan (f64 in $4) */
extern f64 AtanDouble_127d68(f64);           /* soft-double atan (f64 in $4) */

/* Horizontal FOV (degrees) -> vertical FOV (degrees) for a 4:3 aspect:
   2 * atan(0.75 * tan(h / 2)).  The listing's soft-double calls (fptodp,
   dpmul, dptofp) are plain f64 arithmetic here. */
f32 FovHorizToVert_13fbe0(f32 h)
{
    f32 r, f;
    f64 t;

    r = (D_0047D1FC * h) / 180.0f;           /* mul.s pi, $f12; div.s 180.0 */
    r = r / 2.0f;                            /* div.s 2.0 */
    t = Tan_1289b8((f64)r);                  /* jal fptodp; jal Tan_1289b8 */
    t = 0.75 * t;                            /* jal dpmul(0x3FE8000000000000, t) */
    t = AtanDouble_127d68(t);                /* jal AtanDouble_127d68 */
    t = 2.0 * t;                             /* jal dpmul(0x4000000000000000, t) */
    f = (f32)t;                              /* jal dptofp */
    return (180.0f * f) / D_0047D1FC;        /* mul.s 180.0, $f0; div.s pi */
}
