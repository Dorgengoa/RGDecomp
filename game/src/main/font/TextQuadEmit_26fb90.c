/* rgp:protos */
#define RGP_SELF_TextQuadEmit_26fb90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } RF;

/*rgp*/
/*rgp*/

void TextQuadEmit_26fb90(void *a, RF *p, RF *q)
{
    RF r1 __attribute__((aligned(16)));
    RF r2 __attribute__((aligned(16)));

    r1 = *p;
    r2 = *q;

    *(s32 *)&r2.w = *(s32 *)&r2.w + (*(s32 *)&r2.y + 1);
    *(s32 *)&r2.z = *(s32 *)&r2.z + (*(s32 *)&r2.x + 1);
    *(s32 *)&r1.w = *(s32 *)&r1.w + *(s32 *)&r1.y;
    *(s32 *)&r1.z = *(s32 *)&r1.z + *(s32 *)&r1.x;

    GsPktSetUV_13ed60(a, *(s32 *)&r2.y, *(s32 *)&r2.x);
    GsPktSetXYZPixel_13f110(a, *(s32 *)&r1.y, *(s32 *)&r1.x, 0);
    GsPktSetUV_13ed60(a, *(s32 *)&r2.w, *(s32 *)&r2.z);
    GsPktSetXYZPixel_13f110(a, *(s32 *)&r1.w, *(s32 *)&r1.z, 0);
}
