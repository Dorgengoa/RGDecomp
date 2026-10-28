/* rgp:protos */
#define RGP_SELF_insect_InsectPieceMoveTo_5157d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005157D0 -- 480 bytes.  A two-case dispatch that TAIL-CALLS ITSELF
 * with mode 0.  The `mula.s`/`madd.s` pair is the contracted `dz*dz + dx*dx`;
 * `sqrt` is the DOUBLE routine at 0x00129160, so the whole quotient is
 * evaluated in double and narrowed once on the assignment -- that is where the
 * float<->double helper calls come from.  The 10000 scale is an INT constant,
 * so mwcc converts it at run time and CSEs the one `cvt.s.w` for both the
 * multiply and the divide. */

typedef struct Obj {
    u8  pad00[0x78];
    f32 f78[3];                     /* +0x78 */
    f32 f84[3];                     /* +0x84 */
    f32 f90[3];                     /* +0x90 */
    u8  pad9C[0xE4 - 0x9C];
    f32 fE4;                        /* +0xE4 */
} Obj;

/*rgp*/          /* sqrt(double) */

/* The soft-double helpers of `(f32)(sqrt(...) / sp)`, spelled by ADDRESS.
 * Written with the `/` operator mwcc emits the runtime names `fptodp`,
 * `dpdiv`, `dptofp`, and BOTH of those spellings are unusable here:
 *   - `fptodp`/`dptofp` carry no hex in their names, and the overlay linker
 *     (scripts/x_olink.py:unresolved) derives an absolute address from the
 *     trailing hex of an undefined symbol -- a name without one is a HARD
 *     ERROR that fails the whole INSECT link;
 *   - `dpdiv` in config/main.symbols.txt is 0x0013B3F8, which negates its
 *     second operand and tail-calls the ADD routine, i.e. it is dpSUB.  Retail
 *     divides at 0x0013B6E8.
 * Naming all three by address gives byte-identical code AND link-derivable
 * symbols.  See build/ix17/reports/ixb01.md. */
/*rgp*/        /* fptodp -- float to double */
/*rgp*/ /* the REAL soft-double divide */
/*rgp*/        /* dptofp -- double to float */

void insect_InsectPieceMoveTo_5157d0(Obj *o, s32 mode, f32 x, f32 y, f32 z, f32 sp)
{
    f32 dx;
    f32 dz;
    f32 dy;
    f32 n;
    f32 v;
    s32 i;

    o->f84[0] = x;
    o->f84[1] = y;
    o->f84[2] = z;
    if (sp <= 0.0f) {
        sp = 1.0f;
    }
    switch (mode) {
    case 1:
        dx = o->f84[0] - o->f78[0];
        dz = o->f84[2] - o->f78[2];
        if (dx == 0.0f && dz == 0.0f) {
            dy = o->f84[1] - o->f78[1];
            if (dy < 0.0f) {
                dy = -dy;
            }
            sp = dy / sp;
        } else {
            sp = dptofp(dpdiv(Sqrt_129160(fptodp(dx * dx + dz * dz)),
                                             fptodp(sp)));
        }
        insect_InsectPieceMoveTo_5157d0(o, 0, x, y, z, sp);
        break;
    case 0:
        n = (f32)(s32)(sp / o->fE4);
        for (i = 0; i < 3; i++) {
            v = o->f84[i] - o->f78[i];
            v = (f32)(s32)(v * 10000) / 10000;
            o->f90[i] = 0.0f;
            if (v) {
                o->f90[i] = v / n;
            }
        }
        break;
    }
}
