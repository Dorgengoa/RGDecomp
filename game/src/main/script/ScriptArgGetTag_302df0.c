/* rgp:protos */
#define RGP_SELF_ScriptArgGetTag_302df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x0. */

typedef struct Obj_FUN_00302df0 {
    s8 field;         /* +0x00 */
} Obj_FUN_00302df0;

s8 ScriptArgGetTag_302df0(Obj_FUN_00302df0 *o)
{
    return o->field;
}
