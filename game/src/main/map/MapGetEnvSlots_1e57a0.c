/* rgp:protos */
#define RGP_SELF_MapGetEnvSlots_1e57a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x68. */

typedef struct Obj_FUN_001e57a0 {
    u8 pad000[0x68];
    u8 sub[1];         /* +0x68 */
} Obj_FUN_001e57a0;

void *MapGetEnvSlots_1e57a0(Obj_FUN_001e57a0 *o)
{
    return o->sub;
}
