/* rgp:protos */
#define RGP_SELF_TextStyleGetGradientMode_26e320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x34. */

typedef struct Obj_FUN_0026e320 {
    u8 pad000[0x34];
    s16 field;         /* +0x34 */
} Obj_FUN_0026e320;

s16 TextStyleGetGradientMode_26e320(Obj_FUN_0026e320 *o)
{
    return o->field;
}
