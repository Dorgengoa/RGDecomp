/* rgp:protos */
#define RGP_SELF_TextStyleGetZ_26e430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x38. */

typedef struct Obj_FUN_0026e430 {
    u8 pad000[0x38];
    s32 field;         /* +0x38 */
} Obj_FUN_0026e430;

s32 TextStyleGetZ_26e430(Obj_FUN_0026e430 *o)
{
    return o->field;
}
