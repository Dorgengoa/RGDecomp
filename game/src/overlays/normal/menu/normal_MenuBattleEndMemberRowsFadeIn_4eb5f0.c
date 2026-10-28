/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndMemberRowsFadeIn_4eb5f0 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
/* ★★★★★★★ CLOSED / MOVED, s27, BY `#pragma optimization_level 3`.
 * mwcc's DEFAULT here is -O4.  Level 3 is a DISTINCT AXIS from the `opt_*`
 * pragma namespace [[mwcc-pragma-namespace]] enumerates: 14 `opt_*` arms were a
 * clean null on normal_FieldHudLeaderChangedNop_4f50e0 and 23 were a clean null on this unit's
 * residue, while the LEVEL knob moved both.  Screened over all 68 open drafted
 * normal units in build/wf-normal/s27/olevel.log (levels 1/2/3): levels 1 and 2
 * are catastrophic on every unit, level 3 CLOSED normal_FieldHudPartyPanelsStep_4f57f0 and
 * normal_MenuBattleEndMemberRowsFadeIn_4eb5f0 outright and took normal_ShopMenuSellItemStatusLayout_50ef80 and
 * normal_BtlChgMenuWeaponGridDrawCb_503930 from LENGTH-WRONG to the RIGHT LENGTH. */
#include "types.h"
/* normal 0x004EB5F0 -- a true LEAF (no frame): ramps two 0..1 fades per live
 * row of p->fEC, the second only once the first has saturated.  0.1f is
 * MAIN's `.lit4` pool entry at 0x0047D7CC. */
typedef struct E {
    f32 f00;
    u8  pad004[0xC];
    f32 f10;
    u8  pad014[0xC];
} E;

typedef struct N {
    u8  pad000[0x8];
    s32 f08;
    s32 f0C;
    u8  pad010[0xEC - 0x10];
    E  *fEC;
    s8  f0F0[1];
} N;

void normal_MenuBattleEndMemberRowsFadeIn_4eb5f0(N *p)
{
    s32 i;

    for (i = 0; i < p->f08; i++) {
        if (i < p->f0C) {
            if (p->f0F0[i] == 0) {
                p->fEC[i].f00 += 0.1f;
                if (p->fEC[i].f00 >= 1.0f) {
                    p->fEC[i].f00 = 1.0f;
                }
                if (p->fEC[i].f00 == 1.0f) {
                    p->fEC[i].f10 += 0.1f;
                    if (p->fEC[i].f10 >= 1.0f) {
                        p->fEC[i].f10 = 1.0f;
                    }
                }
            }
        }
    }
}
