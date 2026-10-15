#include "types.h"

extern void CaptionGlyphNodeSetCode_340360(void *, s32);
extern void CaptionGlyphNodeSetSheet_340380(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
};

void CaptionGlyphNodeReset_3403b0(struct Obj0 *p0)
{
    p0->m00 = 0;
    CaptionGlyphNodeSetCode_340360(p0, -1);
    CaptionGlyphNodeSetSheet_340380(p0, -1);
    p0->m08 = 0;
}
