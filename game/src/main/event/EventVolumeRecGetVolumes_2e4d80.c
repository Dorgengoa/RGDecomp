/* rgp:protos */
#define RGP_SELF_EventVolumeRecGetVolumes_2e4d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_002e4d80 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_002e4d80;

s32 EventVolumeRecGetVolumes_2e4d80(Obj_FUN_002e4d80 *o)
{
    return o->field;
}
