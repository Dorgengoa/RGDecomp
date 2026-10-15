#include "types.h"

/* Address of the small-data object D_00482A38.  Declared as the 4-byte scalar the %gp_rel addressing requires; the real object behind it may be wider. */

extern s32 D_00482A38;

void *GetObjRefTable_313de0(void)
{
    return &D_00482A38;
}
