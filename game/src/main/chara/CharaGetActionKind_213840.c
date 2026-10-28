/* rgp:protos */
#define RGP_SELF_CharaGetActionKind_213840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xA36. */

typedef struct Obj_FUN_00213840 {
    u8 pad000[0xA36];
    s16 field;         /* +0xA36 */
} Obj_FUN_00213840;

s16 CharaGetActionKind_213840(Obj_FUN_00213840 *o)
{
    return o->field;
}
