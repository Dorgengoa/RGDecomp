/* rgp:protos */
#define RGP_SELF_DataRowClearRuntimeMaybe_417140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x1C. */

typedef struct Obj_FUN_00417140 {
    u8 pad000[0x1C];
    s32 field;         /* +0x1C */
} Obj_FUN_00417140;

void DataRowClearRuntimeMaybe_417140(Obj_FUN_00417140 *o)
{
    o->field = 0;
}
