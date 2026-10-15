#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_0018c540 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_0018c540;

s32 ModelCfgEntryGetModelObjMaybe_18c540(Obj_FUN_0018c540 *o)
{
    return o->field;
}
