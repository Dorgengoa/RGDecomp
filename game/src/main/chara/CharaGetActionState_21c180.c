/* rgp:protos */
#define RGP_SELF_CharaGetActionState_21c180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xA34. */

typedef struct Obj_FUN_0021c180 {
    u8 pad000[0xA34];
    s16 field;         /* +0xA34 */
} Obj_FUN_0021c180;

s16 CharaGetActionState_21c180(Obj_FUN_0021c180 *o)
{
    return o->field;
}
