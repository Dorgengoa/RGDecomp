/* rgp:protos */
#define RGP_SELF_ScriptCallGetArgs_302ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_00302ab0 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_00302ab0;

s32 ScriptCallGetArgs_302ab0(Obj_FUN_00302ab0 *o)
{
    return o->field;
}
