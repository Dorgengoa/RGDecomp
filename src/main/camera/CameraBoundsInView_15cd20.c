#include "types.h"

/* `D_004810A4 ? D_004810A4->mF20 : 0` is the neighbourhood idiom (same shape
   in ProjectDepth_15d0a0).  The second parameter is dead - it survives only as the
   $6 copy in the prologue. */

struct Root {
    u8 pad0000[0xF20];
    u8 *mF20;
};

extern struct Root *D_004810A4;
extern void MtxMul_13d240(void *dst, void *src, void *extra);
extern void AabbInFrustum_13be60(void *a, void *b, void *c, void *d);

void CameraBoundsInView_15cd20(void *p0, void *p1)
{
    u8 buf[0x40];
    u8 *g;

    if (D_004810A4 == 0) {
        g = 0;
    } else {
        g = D_004810A4->mF20;
    }
    MtxMul_13d240(buf, g + 0xB0, p1);
    AabbInFrustum_13be60(p0, buf, g + 0x3D0, g + 0x410);
}
