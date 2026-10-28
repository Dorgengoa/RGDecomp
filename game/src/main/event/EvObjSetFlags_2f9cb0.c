/* rgp:protos */
#define RGP_SELF_EvObjSetFlags_2f9cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xD0. */

typedef struct Obj_FUN_002f9cb0 {
    u8 pad000[0xD0];
    s32 field;         /* +0xD0 */
} Obj_FUN_002f9cb0;

void EvObjSetFlags_2f9cb0(Obj_FUN_002f9cb0 *o, s32 value)
{
    o->field = value;
}
