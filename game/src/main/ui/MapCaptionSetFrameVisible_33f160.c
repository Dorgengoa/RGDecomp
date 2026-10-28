/* rgp:protos */
#define RGP_SELF_MapCaptionSetFrameVisible_33f160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x38. */

typedef struct Obj_FUN_0033f160 {
    u8 pad000[0x38];
    s32 field;         /* +0x38 */
} Obj_FUN_0033f160;

void MapCaptionSetFrameVisible_33f160(Obj_FUN_0033f160 *o, s32 value)
{
    o->field = value;
}
