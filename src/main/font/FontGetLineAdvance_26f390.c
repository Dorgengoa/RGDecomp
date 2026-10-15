#include "types.h"

extern u8 FontGetLineHeight_26f3e0(s32);
extern void TextStyleGetSpacing_26f2e0(s32, void *, void *);

struct Obj0 {
    s32 m00;
};

void FontGetLineAdvance_26f390(s32 p0, struct Obj0 *p1)
{
    s32 v3C;
    s32 v38;
    s32 r0;
    s32 t0;

    r0 = FontGetLineHeight_26f3e0(p0);
    TextStyleGetSpacing_26f2e0(p0, &v3C, &v38);
    t0 = v38;
    p1->m00 = (r0 + t0);
}
