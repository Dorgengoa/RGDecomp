/* rgp:protos */
#define RGP_SELF_EventScriptRecGetEntryCount_2e38a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_002e38a0 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_002e38a0;

s32 EventScriptRecGetEntryCount_2e38a0(Obj_FUN_002e38a0 *o)
{
    return o->field;
}
