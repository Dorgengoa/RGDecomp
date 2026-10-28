/* rgp:protos */
#define RGP_SELF_CharaActFailCountGet_3b6480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x1D8. */

typedef struct Obj_FUN_003b6480 {
    u8 pad000[0x1D8];
    s16 field;         /* +0x1D8 */
} Obj_FUN_003b6480;

s16 CharaActFailCountGet_3b6480(Obj_FUN_003b6480 *o)
{
    return o->field;
}
