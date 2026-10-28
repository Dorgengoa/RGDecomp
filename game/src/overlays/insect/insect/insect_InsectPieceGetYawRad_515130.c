/* rgp:protos */
#define RGP_SELF_insect_InsectPieceGetYawRad_515130 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00515130 -- 56 bytes, 14 instructions.
 * _gp = 0x00485170, so `-0x7F74($28)` is the gp-relative f32 at 0x0047D1FC.
 * `mul.s $f0,$f2,$f0` has the gp float in `fs`, so it is written on the LEFT
 * of the product.  0x43340000 = 180.0f.
 */

extern f32 D_0047D1FC;
/*rgp*/

f32 insect_InsectPieceGetYawRad_515130(void *rgp_a0)
{
    return (D_0047D1FC * insect_InsectPieceGetYawDeg_515170((void *)rgp_a0)) / 180.0f;
}
