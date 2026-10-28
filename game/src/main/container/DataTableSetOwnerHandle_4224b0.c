/* rgp:protos */
#define RGP_SELF_DataTableSetOwnerHandle_4224b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x94. */

typedef struct Obj_FUN_004224b0 {
    u8 pad000[0x94];
    s32 field;         /* +0x94 */
} Obj_FUN_004224b0;

void DataTableSetOwnerHandle_4224b0(Obj_FUN_004224b0 *o, s32 value)
{
    o->field = value;
}
