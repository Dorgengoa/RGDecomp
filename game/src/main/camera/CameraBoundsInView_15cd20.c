/* rgp:protos */
#define RGP_SELF_CameraBoundsInView_15cd20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `D_004810A4 ? D_004810A4->mF20 : 0` is the neighbourhood idiom (same shape
   in ProjectDepth_15d0a0).  The second parameter is dead - it survives only as the
   $6 copy in the prologue. */

struct Root {
    u8 pad0000[0xF20];
    u8 *mF20;
};

extern struct Root *D_004810A4;
/*rgp*/
/*rgp*/

int CameraBoundsInView_15cd20(void *p0, void *p1)
{
    u8 buf[0x40] __attribute__((aligned(16)));
    u8 *g;

    if (D_004810A4 == 0) {
        g = 0;
    } else {
        g = D_004810A4->mF20;
    }
    MtxMul_13d240(buf, g + 0xB0, p1);
    return AabbInFrustum_13be60(p0, buf, g + 0x3D0, g + 0x410);
}
