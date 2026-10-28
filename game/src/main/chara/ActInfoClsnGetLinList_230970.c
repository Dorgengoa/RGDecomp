/* rgp:protos */
#define RGP_SELF_ActInfoClsnGetLinList_230970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_00230970 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_00230970;

s32 ActInfoClsnGetLinList_230970(Obj_FUN_00230970 *o)
{
    return o->field;
}
