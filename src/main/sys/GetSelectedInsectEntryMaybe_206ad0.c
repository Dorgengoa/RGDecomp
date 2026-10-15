#include "types.h"

/* Address of the small-data object D_00481BA8.  Declared as the 4-byte scalar the %gp_rel addressing requires; the real object behind it may be wider. */

extern s32 D_00481BA8;

void *GetSelectedInsectEntryMaybe_206ad0(void)
{
    return &D_00481BA8;
}
