/* rgp:protos */
#define RGP_SELF_ActCfgTableGetName_223cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_00223cf0 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_00223cf0;

s32 ActCfgTableGetName_223cf0(Obj_FUN_00223cf0 *o)
{
    return o->field;
}
