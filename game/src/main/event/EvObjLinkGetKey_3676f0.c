/* rgp:protos */
#define RGP_SELF_EvObjLinkGetKey_3676f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xE0. */

typedef struct Obj_FUN_003676f0 {
    u8 pad000[0xE0];
    s32 field;         /* +0xE0 */
} Obj_FUN_003676f0;

s32 EvObjLinkGetKey_3676f0(Obj_FUN_003676f0 *o)
{
    return o->field;
}
