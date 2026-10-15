#include "types.h"

extern void LoadHandleReset_1ccc10(void *);
extern void MapCaptionSetOffsetY_33f1f0(void *, s32);
extern void MapCaptionSetOffsetX_33f1d0(void *, s32);
extern void MapCaptionSetImageMode_33f1b0(void *, s32);
extern void MapCaptionSetWaitFrames_33f180(void *, s32);
extern void MapCaptionSetFrameVisible_33f160(void *, s32);
extern void MapCaptionSetGlyphSpacing_33f140(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482CB0;

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    u8 m24;
};

void MapCaptionInit_33fd90(struct Obj0 *p0)
{
    LoadHandleReset_1ccc10(p0);
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m20 = 0;
    p0->m24 = 0;
    MapCaptionSetOffsetY_33f1f0(p0, 0);
    MapCaptionSetOffsetX_33f1d0(p0, 0);
    MapCaptionSetImageMode_33f1b0(p0, 0);
    MapCaptionSetWaitFrames_33f180(p0, 0x3C);
    MapCaptionSetFrameVisible_33f160(p0, 1);
    MapCaptionSetGlyphSpacing_33f140(p0, 0);
    D_00482CB0 = 0;
}
