/* rgp:protos */
#define RGP_SELF_MapLinkGetTopAttrMaybe_1e9230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x1C. */

typedef struct Obj_FUN_001e9230 {
    u8 pad000[0x1C];
    s32 field;         /* +0x1C */
} Obj_FUN_001e9230;

s32 MapLinkGetTopAttrMaybe_1e9230(Obj_FUN_001e9230 *o)
{
    return o->field;
}
