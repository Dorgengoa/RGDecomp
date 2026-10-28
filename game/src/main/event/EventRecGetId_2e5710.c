/* rgp:protos */
#define RGP_SELF_EventRecGetId_2e5710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_002e5710 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_002e5710;

s32 EventRecGetId_2e5710(Obj_FUN_002e5710 *o)
{
    return o->field;
}
