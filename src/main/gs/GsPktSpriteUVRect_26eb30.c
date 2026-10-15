#include "types.h"

typedef struct { f32 x, y, z, w; } RF;
typedef struct { s32 x, y, z, w; } RI;
typedef union { RF f; RI i; } R;

extern void GsPktSetUV_13ed60(void *, s32, s32);
extern void GsPktSetXYZPixel_13f110(void *, s32, s32, s32);

void GsPktSpriteUVRect_26eb30(void *a, RF *p, RF *q, s32 d)
{
    RF r1;
    RF r2;

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
