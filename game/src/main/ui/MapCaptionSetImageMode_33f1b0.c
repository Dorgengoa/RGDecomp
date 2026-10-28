/* rgp:protos */
#define RGP_SELF_MapCaptionSetImageMode_33f1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x30. */

typedef struct Obj_FUN_0033f1b0 {
    u8 pad000[0x30];
    s16 field;         /* +0x30 */
} Obj_FUN_0033f1b0;

void MapCaptionSetImageMode_33f1b0(Obj_FUN_0033f1b0 *o, s16 value)
{
    o->field = value;
}
