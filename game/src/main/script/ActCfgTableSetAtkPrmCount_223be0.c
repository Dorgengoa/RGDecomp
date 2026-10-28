/* rgp:protos */
#define RGP_SELF_ActCfgTableSetAtkPrmCount_223be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x74. */

typedef struct Obj_FUN_00223be0 {
    u8 pad000[0x74];
    s16 field;         /* +0x74 */
} Obj_FUN_00223be0;

void ActCfgTableSetAtkPrmCount_223be0(Obj_FUN_00223be0 *o, s16 value)
{
    o->field = value;
}
