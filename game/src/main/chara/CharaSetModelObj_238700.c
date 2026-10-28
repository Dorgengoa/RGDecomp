/* rgp:protos */
#define RGP_SELF_CharaSetModelObj_238700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x3F4. */

typedef struct Obj_FUN_00238700 {
    u8 pad000[0x3F4];
    s32 field;         /* +0x3F4 */
} Obj_FUN_00238700;

void CharaSetModelObj_238700(Obj_FUN_00238700 *o, s32 value)
{
    o->field = value;
}
