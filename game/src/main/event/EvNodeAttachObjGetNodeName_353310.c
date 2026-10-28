/* rgp:protos */
#define RGP_SELF_EvNodeAttachObjGetNodeName_353310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x130. */

typedef struct Obj_FUN_00353310 {
    u8 pad000[0x130];
    s32 field;         /* +0x130 */
} Obj_FUN_00353310;

s32 EvNodeAttachObjGetNodeName_353310(Obj_FUN_00353310 *o)
{
    return o->field;
}
