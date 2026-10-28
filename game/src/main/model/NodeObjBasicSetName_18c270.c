/* rgp:protos */
#define RGP_SELF_NodeObjBasicSetName_18c270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x74. */

typedef struct Obj_FUN_0018c270 {
    u8 pad000[0x74];
    s32 field;         /* +0x74 */
} Obj_FUN_0018c270;

void NodeObjBasicSetName_18c270(Obj_FUN_0018c270 *o, s32 value)
{
    o->field = value;
}
