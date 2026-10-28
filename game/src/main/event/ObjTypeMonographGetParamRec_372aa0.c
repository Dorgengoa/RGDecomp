/* rgp:protos */
#define RGP_SELF_ObjTypeMonographGetParamRec_372aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xE4. */

typedef struct Obj_FUN_00372aa0 {
    u8 pad000[0xE4];
    s32 field;         /* +0xE4 */
} Obj_FUN_00372aa0;

s32 ObjTypeMonographGetParamRec_372aa0(Obj_FUN_00372aa0 *o)
{
    return o->field;
}
