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

extern s32 GetCurrentScene_1f5be0(void);
extern s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);
extern void LightningStopByOwner_2d7190(void *, s32);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetActScopeId_214a70(s32);
extern s32 ActionMgrFindTableByScopeId_233c20(s32, s32);
extern void ActCfgTableRunEvntByName_21f680(s32, s32, void *);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectKill_2e06c0(s32, void *);

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
        w = GetActionMgr_1fdb50();
        h = ActionMgrFindById_233b50(w, self->f14);
        if (h != 0) {
            h = ActionMgrFindTableByScopeId_233c20(w, CharaGetActScopeId_214a70(h));
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
        h = GetEffectMgr_2d9040();
        if (self->f20 != -1) {
            EffectKill_2e06c0(h, &self->f1C);
        }
    }
}
