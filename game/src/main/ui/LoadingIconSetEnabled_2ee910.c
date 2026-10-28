/* rgp:protos */
#define RGP_SELF_LoadingIconSetEnabled_2ee910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data u8 D_00482788.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern u8 D_00482788;

void LoadingIconSetEnabled_2ee910(u8 value)
{
    D_00482788 = value;
}
