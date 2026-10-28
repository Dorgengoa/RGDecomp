/* rgp:protos */
#define RGP_SELF_MapBoxGetBlockId_1ddef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x4E. */

typedef struct Obj_FUN_001ddef0 {
    u8 pad000[0x4E];
    s16 field;         /* +0x4E */
} Obj_FUN_001ddef0;

s16 MapBoxGetBlockId_1ddef0(Obj_FUN_001ddef0 *o)
{
    return o->field;
}
