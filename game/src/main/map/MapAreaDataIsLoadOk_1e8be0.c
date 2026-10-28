/* rgp:protos */
#define RGP_SELF_MapAreaDataIsLoadOk_1e8be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x16BC. */

typedef struct Obj_FUN_001e8be0 {
    u8 pad000[0x16BC];
    u8 field;         /* +0x16BC */
} Obj_FUN_001e8be0;

u8 MapAreaDataIsLoadOk_1e8be0(Obj_FUN_001e8be0 *o)
{
    return o->field;
}
