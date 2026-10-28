/* rgp:protos */
#define RGP_SELF_MapMgrGetCaption_1e56c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x18E8. */

typedef struct Obj_FUN_001e56c0 {
    u8 pad000[0x18E8];
    u8 sub[1];         /* +0x18E8 */
} Obj_FUN_001e56c0;

void *MapMgrGetCaption_1e56c0(Obj_FUN_001e56c0 *o)
{
    return o->sub;
}
