/* rgp:protos */
#define RGP_SELF_TargetMngClearAimMode_31ed40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x140. */

typedef struct Obj_FUN_0031ed40 {
    u8 pad000[0x140];
    s32 field;         /* +0x140 */
} Obj_FUN_0031ed40;

void TargetMngClearAimMode_31ed40(Obj_FUN_0031ed40 *o)
{
    o->field = 0;
}
