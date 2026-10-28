/* rgp:protos */
#define RGP_SELF_MapCaptionGetText_33fa00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_0033fa00 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_0033fa00;

s32 MapCaptionGetText_33fa00(Obj_FUN_0033fa00 *o)
{
    return o->field;
}
