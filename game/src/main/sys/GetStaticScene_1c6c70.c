/* rgp:protos */
#define RGP_SELF_GetStaticScene_1c6c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004A7000.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004A7000[];

void *GetStaticScene_1c6c70(void)
{
    return D_004A7000;
}
