/* rgp:protos */
#define RGP_SELF_CharaGetActInfoBlock_214cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x580. */

typedef struct Obj_FUN_00214cc0 {
    u8 pad000[0x580];
    s32 field;         /* +0x580 */
} Obj_FUN_00214cc0;

s32 CharaGetActInfoBlock_214cc0(Obj_FUN_00214cc0 *o)
{
    return o->field;
}
