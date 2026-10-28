/* rgp:protos */
#define RGP_SELF_MapMgrSetHeap_1e33f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x64. */

typedef struct Obj_FUN_001e33f0 {
    u8 pad000[0x64];
    s32 field;         /* +0x64 */
} Obj_FUN_001e33f0;

void MapMgrSetHeap_1e33f0(Obj_FUN_001e33f0 *o, s32 value)
{
    o->field = value;
}
