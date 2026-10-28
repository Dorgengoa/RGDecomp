/* rgp:protos */
#define RGP_SELF_EventRecGetAreaId_2e5700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_002e5700 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_002e5700;

s32 EventRecGetAreaId_2e5700(Obj_FUN_002e5700 *o)
{
    return o->field;
}
