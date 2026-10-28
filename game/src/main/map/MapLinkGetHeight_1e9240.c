/* rgp:protos */
#define RGP_SELF_MapLinkGetHeight_1e9240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_001e9240 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_001e9240;

s32 MapLinkGetHeight_1e9240(Obj_FUN_001e9240 *o)
{
    return o->field;
}
