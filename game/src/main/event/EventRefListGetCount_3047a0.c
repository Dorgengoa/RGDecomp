/* rgp:protos */
#define RGP_SELF_EventRefListGetCount_3047a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_003047a0 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_003047a0;

s32 EventRefListGetCount_3047a0(Obj_FUN_003047a0 *o)
{
    return o->field;
}
