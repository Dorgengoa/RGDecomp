/* rgp:protos */
#define RGP_SELF_ActDataSetCnctCount_225ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x24. */

typedef struct Obj_FUN_00225ca0 {
    u8 pad000[0x24];
    s16 field;         /* +0x24 */
} Obj_FUN_00225ca0;

void ActDataSetCnctCount_225ca0(Obj_FUN_00225ca0 *o, s16 value)
{
    o->field = value;
}
