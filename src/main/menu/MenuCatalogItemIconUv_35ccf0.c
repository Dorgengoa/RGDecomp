#include "types.h"

void MenuCatalogItemIconUv_35ccf0(s32 p0, s32 p1, s32 *p2, s32 *p3)
{
    if (p1 >= 0x14) {
        *p2 = (p1 % 4) * 128;
        *p3 = 0xCE;
        return;
    }
    *p2 = (p1 % 4) * 64;
    *p3 = (p1 / 4) * 50;
}
