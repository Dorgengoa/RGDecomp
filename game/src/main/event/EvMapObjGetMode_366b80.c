/* rgp:protos */
#define RGP_SELF_EvMapObjGetMode_366b80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x300. */

typedef struct Obj_FUN_00366b80 {
    u8 pad000[0x300];
    s16 field;         /* +0x300 */
} Obj_FUN_00366b80;

s16 EvMapObjGetMode_366b80(Obj_FUN_00366b80 *o)
{
    return o->field;
}
