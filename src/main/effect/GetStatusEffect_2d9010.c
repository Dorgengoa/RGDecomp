#include "types.h"

/* Address of the small-data object D_004826B0.  Declared as the 4-byte scalar the %gp_rel addressing requires; the real object behind it may be wider. */

extern s32 D_004826B0;

void *GetStatusEffect_2d9010(void)
{
    return &D_004826B0;
}
