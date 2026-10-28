/* rgp:protos */
#define RGP_SELF_CharaGetFlags_2124b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s64 at +0x568. */

typedef struct Obj_FUN_002124b0 {
    u8 pad000[0x568];
    s64 field;         /* +0x568 */
} Obj_FUN_002124b0;

s64 CharaGetFlags_2124b0(Obj_FUN_002124b0 *o)
{
    return o->field;
}
