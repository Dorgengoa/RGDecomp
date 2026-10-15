#include "types.h"

/* Address of the sub-object at +0xA0. */

typedef struct Obj_FUN_001e8bf0 {
    u8 pad000[0xA0];
    u8 sub[1];         /* +0xA0 */
} Obj_FUN_001e8bf0;

void *MapAreaDataGetSceneCfg_1e8bf0(Obj_FUN_001e8bf0 *o)
{
    return o->sub;
}
