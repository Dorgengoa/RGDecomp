/* rgp:protos */
#define RGP_SELF_CharaTableGetActionKind_225d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x26. */

typedef struct Obj_FUN_00225d30 {
    u8 pad000[0x26];
    s16 field;         /* +0x26 */
} Obj_FUN_00225d30;

s16 CharaTableGetActionKind_225d30(Obj_FUN_00225d30 *o)
{
    return o->field;
}
