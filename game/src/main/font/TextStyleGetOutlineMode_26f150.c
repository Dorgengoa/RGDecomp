/* rgp:protos */
#define RGP_SELF_TextStyleGetOutlineMode_26f150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x0. */

typedef struct Obj_FUN_0026f150 {
    s8 field;         /* +0x00 */
} Obj_FUN_0026f150;

s8 TextStyleGetOutlineMode_26f150(Obj_FUN_0026f150 *o)
{
    return o->field;
}
