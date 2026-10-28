/* rgp:protos */
#define RGP_SELF_CharaTableDataGetTimePrmtList_226970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x1C. */

typedef struct Obj_FUN_00226970 {
    u8 pad000[0x1C];
    s32 field;         /* +0x1C */
} Obj_FUN_00226970;

s32 CharaTableDataGetTimePrmtList_226970(Obj_FUN_00226970 *o)
{
    return o->field;
}
