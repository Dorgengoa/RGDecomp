/* rgp:protos */
#define RGP_SELF_CharaIsActionActive_215040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is the s16 at +0xA38 non-zero? */

typedef struct Obj_FUN_00215040 {
    u8 pad000[0xA38];
    s16 field;         /* +0xA38 */
} Obj_FUN_00215040;

u8 CharaIsActionActive_215040(Obj_FUN_00215040 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
