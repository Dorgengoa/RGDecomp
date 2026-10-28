/* rgp:protos */
#define RGP_SELF_CharaTableDataGetTimeClsnList_2269b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_002269b0 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_002269b0;

s32 CharaTableDataGetTimeClsnList_2269b0(Obj_FUN_002269b0 *o)
{
    return o->field;
}
