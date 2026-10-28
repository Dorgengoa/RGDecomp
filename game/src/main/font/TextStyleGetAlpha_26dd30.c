/* rgp:protos */
#define RGP_SELF_TextStyleGetAlpha_26dd30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x6. */

typedef struct Obj_FUN_0026dd30 {
    u8 pad000[0x6];
    s16 field;         /* +0x6 */
} Obj_FUN_0026dd30;

s16 TextStyleGetAlpha_26dd30(Obj_FUN_0026dd30 *o)
{
    return o->field;
}
