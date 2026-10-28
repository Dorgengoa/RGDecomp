/* rgp:protos */
#define RGP_SELF_GsPktSpriteUVRect_26eb30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } RF;
typedef struct { s32 x, y, z, w; } RI;
typedef union { RF f; RI i; } R;

/*rgp*/
/*rgp*/

void GsPktSpriteUVRect_26eb30(void *a, RF *p, RF *q, s32 d)
{
    RF r1 __attribute__((aligned(16)));
    RF r2 __attribute__((aligned(16)));

    r1 = *p;
    r2 = *q;

    *(s32 *)&r2.z = *(s32 *)&r2.z + *(s32 *)&r2.x;
    *(s32 *)&r2.w = *(s32 *)&r2.w + *(s32 *)&r2.y;
    *(s32 *)&r1.z = *(s32 *)&r1.z + (*(s32 *)&r1.x - 1);
    *(s32 *)&r1.w = *(s32 *)&r1.w + (*(s32 *)&r1.y - 1);

    GsPktSetUV_13ed60(a, *(s32 *)&r2.x, *(s32 *)&r2.y);
    GsPktSetXYZPixel_13f110(a, *(s32 *)&r1.x, *(s32 *)&r1.y, d);
    GsPktSetUV_13ed60(a, *(s32 *)&r2.z, *(s32 *)&r2.w);
    GsPktSetXYZPixel_13f110(a, *(s32 *)&r1.z, *(s32 *)&r1.w, d);
}
