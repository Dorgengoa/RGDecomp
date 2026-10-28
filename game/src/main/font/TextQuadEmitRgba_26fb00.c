/* rgp:protos */
#define RGP_SELF_TextQuadEmitRgba_26fb00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V_0026fb00;

/*rgp*/
/*rgp*/

void TextQuadEmitRgba_26fb00(void *p, V_0026fb00 *a, V_0026fb00 *b, u8 *c)
{
    V_0026fb00 x __attribute__((aligned(16)));
    V_0026fb00 y __attribute__((aligned(16)));

    x = *a;
    y = *b;
    GsPktSetRGBAQ_13ee40(p, c[0], c[1], c[2], c[3]);
    TextQuadEmit_26fb90(p, &x, &y);
}
