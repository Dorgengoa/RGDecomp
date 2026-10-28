/* rgp:protos */
#define RGP_SELF_EventPathRecGetPoints_2e4180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_002e4180 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_002e4180;

s32 EventPathRecGetPoints_2e4180(Obj_FUN_002e4180 *o)
{
    return o->field;
}
