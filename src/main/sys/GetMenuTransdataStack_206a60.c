#include "types.h"

/* Address of the static object D_004BBF80.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BBF80[];

void *GetMenuTransdataStack_206a60(void)
{
    return D_004BBF80;
}
