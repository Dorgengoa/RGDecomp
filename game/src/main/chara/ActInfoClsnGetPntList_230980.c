/* rgp:protos */
#define RGP_SELF_ActInfoClsnGetPntList_230980 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_00230980 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00230980;

s32 ActInfoClsnGetPntList_230980(Obj_FUN_00230980 *o)
{
    return o->field;
}
