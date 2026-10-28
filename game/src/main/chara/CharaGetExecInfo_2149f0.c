/* rgp:protos */
#define RGP_SELF_CharaGetExecInfo_2149f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x8B0. */

typedef struct Obj_FUN_002149f0 {
    u8 pad000[0x8B0];
    u8 sub[1];         /* +0x8B0 */
} Obj_FUN_002149f0;

void *CharaGetExecInfo_2149f0(Obj_FUN_002149f0 *o)
{
    return o->sub;
}
