#include "types.h"

extern void * GetCurrentScene_1f5be0(void);
extern s32 ScreenFadeSetOverlayMaybe_1cf540(void *, s32, s32, s32);
extern void ScreenFadeSetOverlayZoomMaybe_1cf530(void *, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x58B4];
    s16 m58B4;
    s16 m58B6;
};

void SceneScreenOverlayResetMaybe_2f1ea0(void)
{
    struct Obj0 *r0;
    s32 r1;

    r0 = GetCurrentScene_1f5be0();
    r1 = ScreenFadeSetOverlayMaybe_1cf540(r0, 0, 0, 0);
    ScreenFadeSetOverlayZoomMaybe_1cf530(r0, 1.0f, 0.0f, 0.0f);
    r0->m58B4 = 0;
    r0->m58B6 = 0;
}
