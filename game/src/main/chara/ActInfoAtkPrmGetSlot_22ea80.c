/* rgp:protos */
#define RGP_SELF_ActInfoAtkPrmGetSlot_22ea80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_0022ea80 {
    s16 field;         /* +0x00 */
} Obj_FUN_0022ea80;

s16 ActInfoAtkPrmGetSlot_22ea80(Obj_FUN_0022ea80 *o)
{
    return o->field;
}
