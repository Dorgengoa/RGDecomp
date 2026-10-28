/* rgp:protos */
#define RGP_SELF_EventVolumeRecGetCount_2e4d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_002e4d90 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_002e4d90;

s32 EventVolumeRecGetCount_2e4d90(Obj_FUN_002e4d90 *o)
{
    return o->field;
}
