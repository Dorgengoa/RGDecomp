/* rgp:protos */
#define RGP_SELF_CharaTableDataGetTimeMoveList_226990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_00226990 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_00226990;

s32 CharaTableDataGetTimeMoveList_226990(Obj_FUN_00226990 *o)
{
    return o->field;
}
