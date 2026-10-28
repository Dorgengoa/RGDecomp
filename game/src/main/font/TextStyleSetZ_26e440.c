/* rgp:protos */
#define RGP_SELF_TextStyleSetZ_26e440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x38. */

typedef struct Obj_FUN_0026e440 {
    u8 pad000[0x38];
    s32 field;         /* +0x38 */
} Obj_FUN_0026e440;

void TextStyleSetZ_26e440(Obj_FUN_0026e440 *o, s32 value)
{
    o->field = value;
}
