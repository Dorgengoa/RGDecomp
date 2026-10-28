/* rgp:protos */
#define RGP_SELF_TextStyleSetOutlineMode_26f160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x0. */

typedef struct Obj_FUN_0026f160 {
    u8 field;         /* +0x00 */
} Obj_FUN_0026f160;

void TextStyleSetOutlineMode_26f160(Obj_FUN_0026f160 *o, u8 value)
{
    o->field = value;
}
