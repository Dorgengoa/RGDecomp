/* rgp:protos */
#define RGP_SELF_CharaTableDataGetTimeAcclList_2269a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_002269a0 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_002269a0;

s32 CharaTableDataGetTimeAcclList_2269a0(Obj_FUN_002269a0 *o)
{
    return o->field;
}
