/* rgp:protos */
#define RGP_SELF_EvMapObjGetBreakSe_366b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x32C. */

typedef struct Obj_FUN_00366b40 {
    u8 pad000[0x32C];
    s16 field;         /* +0x32C */
} Obj_FUN_00366b40;

s16 EvMapObjGetBreakSe_366b40(Obj_FUN_00366b40 *o)
{
    return o->field;
}
