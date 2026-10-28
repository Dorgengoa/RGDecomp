/* rgp:protos */
#define RGP_SELF_CharaTableGetName_225480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x28. */

typedef struct Obj_FUN_00225480 {
    u8 pad000[0x28];
    s32 field;         /* +0x28 */
} Obj_FUN_00225480;

s32 CharaTableGetName_225480(Obj_FUN_00225480 *o)
{
    return o->field;
}
