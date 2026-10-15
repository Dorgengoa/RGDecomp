#include "types.h"

/* MEASURED: the four-word block coming out of the temp is FOUR EXPLICIT
   word stores, not a struct assignment.  mwcc's scheduler batches them
   lw/lw/lw - sw/sw/sw - lw/sw, which reads exactly like a struct copy but
   is not: every struct-typed spelling of the second copy (int struct, union,
   s64 pair, by-value parameter) is ONE object and eight words wrong, because
   the copy inherits the FLOAT member type of the first copy's source.
   The first copy IS a struct assignment (lwc1/swc1). */

typedef struct V4f {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4f;

void CaptionCfgSetGlyphOrigin_33feb0(u8 *p0, V4f *p1)
{
    V4f t;

    t = *p1;
    *(s32 *)(p0 + 0x2C) = *(s32 *)&t.x;
    *(s32 *)(p0 + 0x30) = *(s32 *)&t.y;
    *(s32 *)(p0 + 0x34) = *(s32 *)&t.z;
    *(s32 *)(p0 + 0x38) = *(s32 *)&t.w;
}
