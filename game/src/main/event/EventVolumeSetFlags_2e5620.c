/* rgp:protos */
#define RGP_SELF_EventVolumeSetFlags_2e5620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x0. */

typedef struct Obj_FUN_002e5620 {
    s32 field;         /* +0x00 */
} Obj_FUN_002e5620;

void EventVolumeSetFlags_2e5620(Obj_FUN_002e5620 *o, s32 value)
{
    o->field = value;
}
