/* rgp:protos */
#define RGP_SELF_CharaTable2x5x2Set_3ac8a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void CharaTable2x5x2Set_3ac8a0(u8 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    if (p1 >= 0) {
        if (p1 < 2) {
            if (p2 >= 0) {
                if (p2 < 5) {
                    if (p4 >= 0) {
                        if (p4 < 2) {
                            goto ok;
                        }
                    }
                }
            }
        }
    }
    return;
ok:
    *(s32 *)((p4 << 2) + ((p2 << 3) + (((p1 * 5) << 3) - (0 - (s32)p0))) + 0x290) = p3;
}
