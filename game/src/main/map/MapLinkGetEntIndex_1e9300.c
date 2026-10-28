/* rgp:protos */
#define RGP_SELF_MapLinkGetEntIndex_1e9300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_001e9300 {
    s32 field;         /* +0x00 */
} Obj_FUN_001e9300;

s32 MapLinkGetEntIndex_1e9300(Obj_FUN_001e9300 *o)
{
    return o->field;
}
