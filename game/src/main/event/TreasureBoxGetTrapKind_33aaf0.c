/* rgp:protos */
#define RGP_SELF_TreasureBoxGetTrapKind_33aaf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
struct Obj0 { u8 pad000[0x22]; s16 m22; u8 pad024[0x44]; s32 m68; };

s32 TreasureBoxGetTrapKind_33aaf0(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;

    if (p0->m68 == 0) {
        return 0;
    }
    r0 = TreasureBoxIsOpened_33a240(p0);
    if (r0 != 0) {
        return 0;
    }
    r1 = TreasureBoxIsTrapBox_33ab60(p0);
    if (r1 != 0) {
        return (p0->m22 % 3) + 1;
    }
    return 0;
}
