#include "types.h"

/* title.bin overlay, 0x004ECD30 -- lh $2, -0xFE4($28) in the jr delay slot */

extern s16 D_0048418C;

s16 title_TitleGetSelection_4ecd30(void)
{
    return D_0048418C;
}
