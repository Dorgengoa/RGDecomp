#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x26C];
    s8 m26C;
};

extern void CameraDebugFreeUpdate_305c60(struct Obj0 *, s32, s32);

void CameraModeDebugFreeUpdate_307af0(struct Obj0 *p0)
{
    s8 t0;

    t0 = p0->m26C;
    CameraDebugFreeUpdate_305c60(p0, 5, t0);
}
