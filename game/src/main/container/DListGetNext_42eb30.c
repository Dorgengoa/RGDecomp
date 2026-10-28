/* rgp:protos */
#define RGP_SELF_DListGetNext_42eb30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_0042eb30 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0042eb30;

s32 DListGetNext_42eb30(Obj_FUN_0042eb30 *o)
{
    return o->field;
}
