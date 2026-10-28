/* rgp:protos */
#define RGP_SELF_DListGetTail_42ea50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_0042ea50 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0042ea50;

s32 DListGetTail_42ea50(Obj_FUN_0042ea50 *o)
{
    return o->field;
}
