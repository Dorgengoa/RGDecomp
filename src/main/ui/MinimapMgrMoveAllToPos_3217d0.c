#include "types.h"

typedef struct V4 { f32 x, y, z, w; } V4;
s32 MinimapSlotIsActive_322510(s32);
s32 MinimapScrollToClamped_324530(s32, V4 *, s32, s32);

s32 MinimapMgrMoveAllToPos_3217d0(void *arg0, V4 *arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 p;
    s32 q;
    V4 v;
    u8 *b;
    u32 n;
    i = 0;
    do {
        p = (s32)((u8 *)arg0 + i * 0x1B0);
        if (MinimapSlotIsActive_322510(p) != 0) {
            b = (u8 *)&v;
            n = 0x10;
            if (b != NULL) {
                do {
                    *b = 0;
                    n--;
                    b++;
                } while (n != 0);
            }
            v.x = arg1->x;
            v.y = arg1->y;
            v.z = arg1->z;
            MinimapScrollToClamped_324530(p, &v, arg2, arg3);
        }
        i++;
    } while (i < 3);
    q = *(s32 *)((u8 *)arg0 + 0x510);
    if (q == 0) {
        q = *(s32 *)((u8 *)arg0 + 0x514);
    }
    if (q == 0) {
        return 0;
    }
    if (MinimapSlotIsActive_322510(q) != 0 && MinimapScrollToClamped_324530(q, arg1, arg2, arg3) == 0) {
        return 0;
    }
    return 1;
}
