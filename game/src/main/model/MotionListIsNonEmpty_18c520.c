/* rgp:protos */
#define RGP_SELF_MotionListIsNonEmpty_18c520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is the s32 at +0x4 non-zero? */

typedef struct Obj_FUN_0018c520 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0018c520;

u8 MotionListIsNonEmpty_18c520(Obj_FUN_0018c520 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
