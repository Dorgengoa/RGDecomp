/* rgp:protos */
#define RGP_SELF_CharaTableEntrySetEndMotionEnd_2260b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s16 at +0x3A. */

typedef struct Obj_FUN_002260b0 {
    u8 pad000[0x3A];
    s16 field;         /* +0x3A */
} Obj_FUN_002260b0;

void CharaTableEntrySetEndMotionEnd_2260b0(Obj_FUN_002260b0 *o)
{
    o->field = 0;
}
