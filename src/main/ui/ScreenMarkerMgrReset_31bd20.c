#include "types.h"

extern s32 ScreenMarkerClearAll_31c060(void *);
extern void ScreenMarkerSetHeightOffset_31a8f0(void *, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x140];
    s32 m140;
    u8 pad144[0xC];
    s32 m150;
    s32 m154;
    s32 m158;
};

void ScreenMarkerMgrReset_31bd20(struct Obj0 *p0)
{
    s32 r0;

    r0 = ScreenMarkerClearAll_31c060(p0);
    p0->m140 = 1;
    ScreenMarkerSetHeightOffset_31a8f0(p0, 24.0f);
    p0->m150 = 0x3F800000;
    p0->m154 = 0;
    p0->m158 = 0;
}
