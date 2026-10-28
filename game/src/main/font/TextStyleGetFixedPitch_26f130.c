/* rgp:protos */
#define RGP_SELF_TextStyleGetFixedPitch_26f130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x2. */

typedef struct Obj_FUN_0026f130 {
    u8 pad000[0x2];
    u8 field;         /* +0x2 */
} Obj_FUN_0026f130;

u8 TextStyleGetFixedPitch_26f130(Obj_FUN_0026f130 *o)
{
    return o->field;
}
