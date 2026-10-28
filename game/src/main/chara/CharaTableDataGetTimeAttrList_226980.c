/* rgp:protos */
#define RGP_SELF_CharaTableDataGetTimeAttrList_226980 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_00226980 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_00226980;

s32 CharaTableDataGetTimeAttrList_226980(Obj_FUN_00226980 *o)
{
    return o->field;
}
