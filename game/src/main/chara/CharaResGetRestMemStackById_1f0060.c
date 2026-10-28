/* rgp:protos */
#define RGP_SELF_CharaResGetRestMemStackById_1f0060 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
struct Obj0 { u8 pad000[0x4]; s16 m04; };

s32 CharaResGetRestMemStackById_1f0060(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 r1;
    s16 t0;

    r0 = (struct Obj0 *)CharaResFindById_1efba0(p0, p1);
    if (r0 == 0) {
        return 0;
    }
    r1 = ((s32)GetCharaDataMgr_1fdb70());
    t0 = r0->m04;
    return CharaDataGetSubRecMemStack_1ed430(r1, t0, 6);
}
