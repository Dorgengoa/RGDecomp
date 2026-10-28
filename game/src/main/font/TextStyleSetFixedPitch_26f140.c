/* rgp:protos */
#define RGP_SELF_TextStyleSetFixedPitch_26f140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x2. */

typedef struct Obj_FUN_0026f140 {
    u8 pad000[0x2];
    u8 field;         /* +0x2 */
} Obj_FUN_0026f140;

void TextStyleSetFixedPitch_26f140(Obj_FUN_0026f140 *o, u8 value)
{
    o->field = value;
}
