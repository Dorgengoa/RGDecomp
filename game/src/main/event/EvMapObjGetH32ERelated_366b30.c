/* rgp:protos */
#define RGP_SELF_EvMapObjGetH32ERelated_366b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x32E. */

typedef struct Obj_FUN_00366b30 {
    u8 pad000[0x32E];
    s16 field;         /* +0x32E */
} Obj_FUN_00366b30;

s16 EvMapObjGetH32ERelated_366b30(Obj_FUN_00366b30 *o)
{
    return o->field;
}
