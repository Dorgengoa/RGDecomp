/* rgp:protos */
#define RGP_SELF_DataTableSetOwnerHandle_421c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x94. */

typedef struct Obj_FUN_00421c30 {
    u8 pad000[0x94];
    s32 field;         /* +0x94 */
} Obj_FUN_00421c30;

void DataTableSetOwnerHandle_421c30(Obj_FUN_00421c30 *o, s32 value)
{
    o->field = value;
}
