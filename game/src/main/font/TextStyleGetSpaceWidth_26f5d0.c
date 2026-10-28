/* rgp:protos */
#define RGP_SELF_TextStyleGetSpaceWidth_26f5d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x5. */

typedef struct Obj_FUN_0026f5d0 {
    u8 pad000[0x5];
    u8 field;         /* +0x5 */
} Obj_FUN_0026f5d0;

u8 TextStyleGetSpaceWidth_26f5d0(Obj_FUN_0026f5d0 *o)
{
    return o->field;
}
