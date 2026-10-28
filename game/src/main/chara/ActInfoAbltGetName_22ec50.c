/* rgp:protos */
#define RGP_SELF_ActInfoAbltGetName_22ec50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0022ec50 {
    s32 field;         /* +0x00 */
} Obj_FUN_0022ec50;

s32 ActInfoAbltGetName_22ec50(Obj_FUN_0022ec50 *o)
{
    return o->field;
}
