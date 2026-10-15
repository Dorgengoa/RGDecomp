#include "types.h"

extern void GetCurrentScene_1f5be0(void);
extern void CameraModeSetTop_309440(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x268];
    s32 m268;
};

void CameraModePush_3093e0(struct Obj0 *p0, s32 p1)
{
    s32 t0;

    GetCurrentScene_1f5be0();
    t0 = p0->m268;
    if (t0 != 0x21) {
        p0->m268 = (t0 + 1);
        CameraModeSetTop_309440(p0, p1);
    }
}
