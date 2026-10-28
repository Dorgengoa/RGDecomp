/* rgp:protos */
#define RGP_SELF_ActInfoAtkPrmGetId_22ea70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x2. */

typedef struct Obj_FUN_0022ea70 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_0022ea70;

s16 ActInfoAtkPrmGetId_22ea70(Obj_FUN_0022ea70 *o)
{
    return o->field;
}
