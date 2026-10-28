/* rgp:protos */
#define RGP_SELF_NpcObjTableRestoreFlags_2fb2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Copy the s16 at +0x222 to +0x220. */

typedef struct Obj_FUN_002fb2b0 {
    u8 pad000[0x220];
    s16 dst;         /* +0x220 */
    s16 src;         /* +0x222 */
} Obj_FUN_002fb2b0;

void NpcObjTableRestoreFlags_2fb2b0(Obj_FUN_002fb2b0 *o)
{
    o->dst = o->src;
}
