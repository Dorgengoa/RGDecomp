#include "types.h"
#pragma opt_common_subs off
typedef struct Ent { s32 a; s32 b; } Ent;

s32 LoaderReleaseById_1cd340(s32, s32);
s32 GetLoaderMgr_1f59d0();
extern Ent D_00454410[8];
extern s16 D_0047FF4C;
extern s16 D_0047FF54;

s32 InsectMenuReleaseRes_398360(void)
{
    s32 n;
    s32 i;
    Ent *e;
    s32 x;

    n = 1;
    if (D_0047FF4C != 0 && D_0047FF54 >= 0) {
        n += 2;
    }
    for (i = 0; i < n; i++) {
        if (D_00454410[i].a != -1) {
            LoaderReleaseById_1cd340(GetLoaderMgr_1f59d0(), (e = &D_00454410[i])->a);
            e->a = -1;
            e->b = 0;
        }
    }
    return 1;
}
