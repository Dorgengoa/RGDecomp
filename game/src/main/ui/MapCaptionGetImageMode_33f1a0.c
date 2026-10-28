/* rgp:protos */
#define RGP_SELF_MapCaptionGetImageMode_33f1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x30. */

typedef struct Obj_FUN_0033f1a0 {
    u8 pad000[0x30];
    s16 field;         /* +0x30 */
} Obj_FUN_0033f1a0;

s16 MapCaptionGetImageMode_33f1a0(Obj_FUN_0033f1a0 *o)
{
    return o->field;
}
