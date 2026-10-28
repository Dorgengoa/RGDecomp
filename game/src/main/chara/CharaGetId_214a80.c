/* rgp:protos */
#define RGP_SELF_CharaGetId_214a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x424. */

typedef struct Obj_FUN_00214a80 {
    u8 pad000[0x424];
    s16 field;         /* +0x424 */
} Obj_FUN_00214a80;

s16 CharaGetId_214a80(Obj_FUN_00214a80 *o)
{
    return o->field;
}
