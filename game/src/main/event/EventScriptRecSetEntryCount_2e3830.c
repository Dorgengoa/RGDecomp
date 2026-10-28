/* rgp:protos */
#define RGP_SELF_EventScriptRecSetEntryCount_2e3830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x14. */

typedef struct Obj_FUN_002e3830 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_002e3830;

void EventScriptRecSetEntryCount_2e3830(Obj_FUN_002e3830 *o, s32 value)
{
    o->field = value;
}
