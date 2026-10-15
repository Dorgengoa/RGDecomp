#include "types.h"

void MenuCatalogRankTrendIconUvMaybe_35cc90(s32 unused, s32 n, s32 *a, s32 *b)
{
    if (n > 0) {
        *a = 0;
        *b = 0x6A;
    } else if (n == 0) {
        *a = 0x16;
        *b = 0x6A;
    } else if (n < 0) {
        *a = 0x2C;
        *b = 0x6A;
    }
}
