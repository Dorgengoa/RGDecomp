#include "types.h"

typedef struct { f32 x, y, z, w; } V_0026fb00;

extern void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
extern void TextQuadEmit_26fb90(void *, V_0026fb00 *, V_0026fb00 *);

void TextQuadEmitRgba_26fb00(void *p, V_0026fb00 *a, V_0026fb00 *b, u8 *c)
{
    V_0026fb00 x;
    V_0026fb00 y;

    x = *a;
    y = *b;
    GsPktSetRGBAQ_13ee40(p, c[0], c[1], c[2], c[3]);
    TextQuadEmit_26fb90(p, &x, &y);
}
