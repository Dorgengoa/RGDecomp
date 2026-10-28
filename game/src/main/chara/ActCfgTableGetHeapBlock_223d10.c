/* rgp:protos */
#define RGP_SELF_ActCfgTableGetHeapBlock_223d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_00223d10 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_00223d10;

s32 ActCfgTableGetHeapBlock_223d10(Obj_FUN_00223d10 *o)
{
    return o->field;
}
