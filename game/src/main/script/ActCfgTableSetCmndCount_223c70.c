/* rgp:protos */
#define RGP_SELF_ActCfgTableSetCmndCount_223c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x62. */

typedef struct Obj_FUN_00223c70 {
    u8 pad000[0x62];
    s16 field;         /* +0x62 */
} Obj_FUN_00223c70;

void ActCfgTableSetCmndCount_223c70(Obj_FUN_00223c70 *o, s16 value)
{
    o->field = value;
}
