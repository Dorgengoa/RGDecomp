/* rgp:protos */
#define RGP_SELF_ScriptCallGetArgc_302aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_00302aa0 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00302aa0;

s32 ScriptCallGetArgc_302aa0(Obj_FUN_00302aa0 *o)
{
    return o->field;
}
