/* rgp:protos */
#define RGP_SELF_StatusEffectSlotStop_33c2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
    s16 f14;
    s16 f16;
    s16 f18;
    s16 f1A;
    s16 f1C;
    s16 f1E;
    s32 f20;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern char D_004E6110[];
extern char D_00462608[];

/* compare chain tests 12 then 4 = the switch's case order REVERSED, so the
   source order is case 4, case 12. */
void StatusEffectSlotStop_33c2b0(Obj *self)
{
    s32 w;
    s32 h;

    SoundStopEntry_1b8bc0(GameSceneSoundSlot5GetHandle_1d0790(GetCurrentScene_1f5be0()), self->f18, self->f1A);
    switch (self->f12) {
    case 4:
        LightningStopByOwner_2d7190(D_004E6110, self->f14);
        self->f10 = 0;
        break;
    case 12:
        w = ((s32)GetActionMgr_1fdb50());
        h = ((s32)ActionMgrFindById_233b50(w, self->f14));
        if (h != 0) {
            h = ((s32)ActionMgrFindTableByScopeId_233c20(w, ((short)CharaGetActScopeId_214a70(h))));
            if (h != 0) {
                ActCfgTableRunEvntByName_21f680(h, self->f14, D_00462608);
                self->f10 = 0;
            }
        }
        break;
    }
    self->f18 = -1;
    self->f1A = -1;
    self->f14 = -1;
    self->f12 = -1;
    if (self->f10 != 0) {
        self->f10 = 0;
        h = ((s32)GetEffectMgr_2d9040());
        if (self->f20 != -1) {
            EffectKill_2e06c0(h, &self->f1C, 0, 0);
        }
    }
}
