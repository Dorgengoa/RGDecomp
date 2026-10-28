/* rgp:protos */
#define RGP_SELF_CameraModeDebugFreeUpdate_307af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x26C];
    s8 m26C;
};

/*rgp*/

void CameraModeDebugFreeUpdate_307af0(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s8 t0;

    t0 = p0->m26C;
    CameraDebugFreeUpdate_305c60(p0, 5, t0, (int)rgp_a3);
}
