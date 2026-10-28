/* rgp:protos */
#define RGP_SELF_ActionMgrGetHeap_234910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x3C. */

typedef struct Obj_FUN_00234910 {
    u8 pad000[0x3C];
    s32 field;         /* +0x3C */
} Obj_FUN_00234910;

s32 ActionMgrGetHeap_234910(Obj_FUN_00234910 *o)
{
    return o->field;
}
