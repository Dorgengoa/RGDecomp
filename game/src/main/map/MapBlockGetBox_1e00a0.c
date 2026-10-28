/* rgp:protos */
#define RGP_SELF_MapBlockGetBox_1e00a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x74. */

typedef struct Obj_FUN_001e00a0 {
    u8 pad000[0x74];
    u8 sub[1];         /* +0x74 */
} Obj_FUN_001e00a0;

void *MapBlockGetBox_1e00a0(Obj_FUN_001e00a0 *o)
{
    return o->sub;
}
