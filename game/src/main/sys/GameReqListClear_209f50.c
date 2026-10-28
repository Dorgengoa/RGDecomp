/* rgp:protos */
#define RGP_SELF_GameReqListClear_209f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s16 at +0x4. */

typedef struct Obj_FUN_00209f50 {
    u8 pad000[0x4];
    s16 field;         /* +0x4 */
} Obj_FUN_00209f50;

void GameReqListClear_209f50(Obj_FUN_00209f50 *o)
{
    o->field = 0;
}
