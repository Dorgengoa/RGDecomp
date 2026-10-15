#include "types.h"

/* Address of the sub-object at +0x12C. */

typedef struct Obj_FUN_0032a8b0 {
    u8 pad000[0x12C];
    u8 sub[1];         /* +0x12C */
} Obj_FUN_0032a8b0;

void *MinimapGetEntryList_32a8b0(Obj_FUN_0032a8b0 *o)
{
    return o->sub;
}
