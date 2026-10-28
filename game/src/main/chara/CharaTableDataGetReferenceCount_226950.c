/* rgp:protos */
#define RGP_SELF_CharaTableDataGetReferenceCount_226950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x24. */

typedef struct Obj_FUN_00226950 {
    u8 pad000[0x24];
    s16 field;         /* +0x24 */
} Obj_FUN_00226950;

s16 CharaTableDataGetReferenceCount_226950(Obj_FUN_00226950 *o)
{
    return o->field;
}
