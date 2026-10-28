/* rgp:protos */
#define RGP_SELF_MapAreaDataGetLinks_1e8c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x16DC. */

typedef struct Obj_FUN_001e8c10 {
    u8 pad000[0x16DC];
    s32 field;         /* +0x16DC */
} Obj_FUN_001e8c10;

s32 MapAreaDataGetLinks_1e8c10(Obj_FUN_001e8c10 *o)
{
    return o->field;
}
