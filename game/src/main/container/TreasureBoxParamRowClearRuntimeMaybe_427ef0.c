/* rgp:protos */
#define RGP_SELF_TreasureBoxParamRowClearRuntimeMaybe_427ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x40. */

typedef struct Obj_FUN_00427ef0 {
    u8 pad000[0x40];
    s32 field;         /* +0x40 */
} Obj_FUN_00427ef0;

void TreasureBoxParamRowClearRuntimeMaybe_427ef0(Obj_FUN_00427ef0 *o)
{
    o->field = 0;
}
