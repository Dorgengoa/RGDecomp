/* rgp:protos */
#define RGP_SELF_ActInfoWepActGetSlot_22ef10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_0022ef10 {
    s16 field;         /* +0x00 */
} Obj_FUN_0022ef10;

s16 ActInfoWepActGetSlot_22ef10(Obj_FUN_0022ef10 *o)
{
    return o->field;
}
