/* rgp:protos */
#define RGP_SELF_TextStyleSetZEnable_26e420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x36. */

typedef struct Obj_FUN_0026e420 {
    u8 pad000[0x36];
    s16 field;         /* +0x36 */
} Obj_FUN_0026e420;

void TextStyleSetZEnable_26e420(Obj_FUN_0026e420 *o, s16 value)
{
    o->field = value;
}
