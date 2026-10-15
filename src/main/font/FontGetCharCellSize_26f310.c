#include "types.h"

extern s32 FontGetGlyphWidth_26f420(s32, s32);
extern s32 FontGetLineHeight_26f3e0(s32);
extern void TextStyleGetSpacing_26f2e0(s32, void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s32 m00;
};

void FontGetCharCellSize_26f310(s32 p0, struct Obj0 *p1, struct Obj1 *p2, s32 p3)
{
    s32 v5C;
    s32 v58;
    s32 r0;
    s32 r1;
    s32 t0;
    s32 t1;

    r0 = FontGetGlyphWidth_26f420(p0, p3) & 0xFF;
    r1 = FontGetLineHeight_26f3e0(p0) & 0xFF;
    TextStyleGetSpacing_26f2e0(p0, &v5C, &v58);
    t0 = v5C;
    p1->m00 = (r0 + t0);
    t1 = v58;
    p2->m00 = (r1 + t1);
}
