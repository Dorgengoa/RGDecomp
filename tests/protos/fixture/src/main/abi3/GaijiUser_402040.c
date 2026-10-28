#include "types.h"
/* the caller's view: an aligned(8) colour struct by value (the dialect stage's bitfield-gcc
   rule pins aligned(8) on RGBAQ-style structs; here the attribute is explicit) */
typedef struct RGBAQ {
    u8 r, g, b, a;
    u32 q;
} __attribute__((aligned(8))) RGBAQ;

extern void GaijiDraw_402000(s32 *out, RGBAQ c);

void GaijiUser_402040(s32 *out, u32 rgba, u32 q)
{
    RGBAQ c;

    c.r = rgba;
    c.g = rgba >> 8;
    c.b = rgba >> 16;
    c.a = rgba >> 24;
    c.q = q;
    GaijiDraw_402000(out, c);
}
