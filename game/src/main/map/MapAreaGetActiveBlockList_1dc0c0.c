/* rgp:protos */
#define RGP_SELF_MapAreaGetActiveBlockList_1dc0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x178. */

typedef struct Obj_FUN_001dc0c0 {
    u8 pad000[0x178];
    u8 sub[1];         /* +0x178 */
} Obj_FUN_001dc0c0;

void *MapAreaGetActiveBlockList_1dc0c0(Obj_FUN_001dc0c0 *o)
{
    return o->sub;
}
