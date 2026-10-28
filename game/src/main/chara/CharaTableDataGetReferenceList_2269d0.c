/* rgp:protos */
#define RGP_SELF_CharaTableDataGetReferenceList_2269d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_002269d0 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_002269d0;

s32 CharaTableDataGetReferenceList_2269d0(Obj_FUN_002269d0 *o)
{
    return o->field;
}
