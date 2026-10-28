/* rgp:protos */
#define RGP_SELF_CharaTableDataAddTimeAccl_2265b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void CharaTableDataAddTimeAccl_2265b0(void *p, void *q, f32 x, f32 y)
{
    u8 *e;
    s32 i;

    e = *(u8 **)((u8 *)p + 0x10);
    if (e != 0) {
        for (i = 0; i < *(s16 *)((u8 *)p + 0x2A); i++, e += 0x10) {
            ActTimeAcclAddInRange_227990(e, q, x, y);
        }
    }
}
