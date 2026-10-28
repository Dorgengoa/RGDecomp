/* rgp:protos */
#define RGP_SELF_CharaEffectGroupsSetPausedHidden_27a300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CharaEffectGroupsSetPausedHidden_27a300(s32 id, s32 p1, s32 p2, s32 flags)
{
    void *a;
    void *b;
    u8 *e;

    a = GetCharaResMgr_1fdb60();
    b = GetEffectMgr_2d9040();
    e = (u8 *)CharaResFindById_1f0530(a, id);
    if (e == 0) {
        return;
    }
    if (flags & 1) {
        EffectGroupSetPaused_2e2c80(b, *(s16 *)(e + 4), p1);
        EffectGroupSetHidden_2e2bd0(b, *(s16 *)(e + 4), p2);
    }
    if (id >= 0 && id < 0xC) {
        if (flags & 2) {
            EffectGroupSetPaused_2e2c80(b, *(s16 *)(e + 4) - 0x3D1, p1);
            EffectGroupSetHidden_2e2bd0(b, *(s16 *)(e + 4) - 0x3D1, p2);
        }
        if (flags & 4) {
            EffectGroupSetPaused_2e2c80(b, *(s16 *)(e + 4) - 0x3DD, p1);
            EffectGroupSetHidden_2e2bd0(b, *(s16 *)(e + 4) - 0x3DD, p2);
        }
    }
}
