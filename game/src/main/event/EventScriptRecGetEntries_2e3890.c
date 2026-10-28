/* rgp:protos */
#define RGP_SELF_EventScriptRecGetEntries_2e3890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_002e3890 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_002e3890;

s32 EventScriptRecGetEntries_2e3890(Obj_FUN_002e3890 *o)
{
    return o->field;
}
