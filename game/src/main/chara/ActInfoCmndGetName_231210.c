/* rgp:protos */
#define RGP_SELF_ActInfoCmndGetName_231210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_00231210 {
    s32 field;         /* +0x00 */
} Obj_FUN_00231210;

s32 ActInfoCmndGetName_231210(Obj_FUN_00231210 *o)
{
    return o->field;
}
