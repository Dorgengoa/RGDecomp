/* rgp:protos */
#define RGP_SELF_DebugTaskItemSetList_208bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x30. */

typedef struct Obj_FUN_00208bc0 {
    u8 pad000[0x30];
    s32 field;         /* +0x30 */
} Obj_FUN_00208bc0;

void DebugTaskItemSetList_208bc0(Obj_FUN_00208bc0 *o, s32 value)
{
    o->field = value;
}
