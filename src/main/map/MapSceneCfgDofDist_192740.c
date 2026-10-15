#include "types.h"

typedef struct { s32 a, b; } T_00192740;
typedef struct { u8 pad[0x1CC]; f32 arr[3]; } G_00192740;

extern f32 VariantGetFloat_15f740(T_00192740 *);
extern G_00192740 *D_004812F4;

s32 MapSceneCfgDofDist_192740(T_00192740 *q, s32 n)
{
    s32 m;
    s32 i;
    f32 f;

    m = n;
    if (n > 2) m = 2;
    for (i = 0; i < m; i++) {
        f = VariantGetFloat_15f740(q++);
        D_004812F4->arr[i] = f;
    }
    return 1;
}
