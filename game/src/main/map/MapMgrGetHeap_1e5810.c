/* rgp:protos */
#define RGP_SELF_MapMgrGetHeap_1e5810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x64. */

typedef struct Obj_FUN_001e5810 {
    u8 pad000[0x64];
    s32 field;         /* +0x64 */
} Obj_FUN_001e5810;

s32 MapMgrGetHeap_1e5810(Obj_FUN_001e5810 *o)
{
    return o->field;
}
