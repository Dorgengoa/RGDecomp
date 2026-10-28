/* rgp:protos */
#define RGP_SELF_CharaGetMoveReq_2149e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x930. */

typedef struct Obj_FUN_002149e0 {
    u8 pad000[0x930];
    u8 sub[1];         /* +0x930 */
} Obj_FUN_002149e0;

void *CharaGetMoveReq_2149e0(Obj_FUN_002149e0 *o)
{
    return o->sub;
}
