/* rgp:protos */
#define RGP_SELF_CharaTableDataSetTimeAttrCount_2268f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x2E. */

typedef struct Obj_FUN_002268f0 {
    u8 pad000[0x2E];
    s16 field;         /* +0x2E */
} Obj_FUN_002268f0;

void CharaTableDataSetTimeAttrCount_2268f0(Obj_FUN_002268f0 *o, s16 value)
{
    o->field = value;
}
