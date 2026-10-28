/* rgp:protos */
#define RGP_SELF_ActionMgrSetHeap_234900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x3C. */

typedef struct Obj_FUN_00234900 {
    u8 pad000[0x3C];
    s32 field;         /* +0x3C */
} Obj_FUN_00234900;

void ActionMgrSetHeap_234900(Obj_FUN_00234900 *o, s32 value)
{
    o->field = value;
}
