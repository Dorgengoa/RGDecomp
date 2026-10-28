/* rgp:protos */
#define RGP_SELF_CharaGetActScopeId_214a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x426. */

typedef struct Obj_FUN_00214a70 {
    u8 pad000[0x426];
    s16 field;         /* +0x426 */
} Obj_FUN_00214a70;

s16 CharaGetActScopeId_214a70(Obj_FUN_00214a70 *o)
{
    return o->field;
}
