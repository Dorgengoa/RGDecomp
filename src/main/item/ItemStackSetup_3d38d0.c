#include "types.h"

/* Same shape as EvDoorObjSetClosed_303bb0, but the stored constant is ALSO the return
   value -- that is what puts it in $2 instead of $3. */

extern void ItemSetup_3d4ff0(void *obj, s32 force);

typedef struct ObjFUN_003d38d0 {
    u8 pad000[0x14];
    s16 timer;
} ObjFUN_003d38d0;

s32 ItemStackSetup_3d38d0(ObjFUN_003d38d0 *obj, s32 force)
{
    ItemSetup_3d4ff0(obj, force);
    obj->timer = 1;
    return 1;
}
