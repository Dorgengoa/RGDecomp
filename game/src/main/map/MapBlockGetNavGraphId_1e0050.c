/* rgp:protos */
#define RGP_SELF_MapBlockGetNavGraphId_1e0050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x70. */

typedef struct Obj_FUN_001e0050 {
    u8 pad000[0x70];
    s32 field;         /* +0x70 */
} Obj_FUN_001e0050;

s32 MapBlockGetNavGraphId_1e0050(Obj_FUN_001e0050 *o)
{
    return o->field;
}
