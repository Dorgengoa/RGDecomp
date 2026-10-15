#include "types.h"

/* Address of the sub-object at +0x930. */

typedef struct Obj_FUN_002db7b0 {
    u8 pad000[0x930];
    u8 sub[1];         /* +0x930 */
} Obj_FUN_002db7b0;

void *EffModelObjGetScriptVm_2db7b0(Obj_FUN_002db7b0 *o)
{
    return o->sub;
}
