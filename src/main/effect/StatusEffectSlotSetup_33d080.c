#include "types.h"

typedef unsigned __int128 u128;

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
    s32 f24;
    f32 f28;
    s32 f2C;
    u8  pad30[0x60];
    s32 f90;
    s32 f94;
} Obj;

struct Rec {
    u8 pad[0x180];
    u128 m180;
};

extern s32 GetCurrentScene_1f5be0(void);
extern s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);
extern struct Rec *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void StatusEffectSlotStop_33c2b0(Obj *);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectCreateByName_2e1020(f32 *, s32, void *, s16);
extern void FxStatusUpDownSpawnMaybe_2d7fd0(s32);
extern void FxStatusUpDownSpawnMaybe_2d7f60(s32);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetActScopeId_214a70(s32);
extern s32 ActionMgrFindTableByScopeId_233c20(s32, s32);
extern void ActCfgTableRunEvntByName_21f680(s32, s32, void *);
extern s32 SoundNextPlayHandle_1b81c0(void);
extern void EffectSetId_2e0100(s32, f32 *, s32);
extern void EffectSetName_2e01c0(s32, f32 *, void *);
extern void EffectSetPos_2e0bb0(s32, f32 *, u128 *);

extern char D_00462638[];
extern char D_00462640[];
extern char D_00462648[];
extern char D_00462650[];
extern char D_00462658[];
extern char D_00462668[];

/* stack locals are allocated in REVERSE declaration order:
   st7 -> 0x60, st6 -> 0x80, st2 -> 0xA0, st0 -> 0xC0, mv -> 0xE0 */
void StatusEffectSlotSetup_33d080(Obj *self, s32 a1, s32 a2, s32 a3)
{
    u128 mv;
    f32 st0[8];
    f32 st2[8];
    f32 st6[8];
    f32 st7[8];
    s32 r;
    struct Rec *rec;
    s32 obj;
    s32 flag;
    s32 w;
    s32 h;

    r = GetCurrentScene_1f5be0();
    SoundStopEntry_1b8bc0(GameSceneSoundSlot5GetHandle_1d0790(r), self->f18, self->f1A);
    self->f18 = -1;
    self->f1A = -1;
    rec = ObjRecGetLiveObject_1c4a90(r, a1);
    if (rec == 0) {
        return;
    }
    StatusEffectSlotStop_33c2b0(self);
    self->f14 = a1;
    self->f12 = a2;
    self->f16 = a3;
    self->f20 = -1;
    mv = rec->m180;
    obj = GetEffectMgr_2d9040();
    flag = 0;
    switch (self->f12) {
    case 1:
        self->f10 = 1;
        self->f90 = 0;
        self->f94 = 0;
        self->f18 = 8;
        break;
    case 3:
        self->f10 = 1;
        self->f90 = 0;
        self->f94 = 0;
        self->f18 = 10;
        break;
    case 4:
        self->f18 = 11;
        self->f10 = 1;
        self->f90 = 0;
        break;
    case 0:
        EffectCreateByName_2e1020(st0, obj, D_00462638, -1);
        self->f1C = *(s16 *)&st0[0];
        self->f20 = *(s32 *)&st0[1];
        self->f24 = *(s32 *)&st0[2];
        self->f28 = st0[3];
        self->f2C = *(s32 *)&st0[4];
        flag = 1;
        self->f18 = 7;
        break;
    case 2:
        EffectCreateByName_2e1020(st2, obj, D_00462640, -1);
        self->f1C = *(s16 *)&st2[0];
        self->f20 = *(s32 *)&st2[1];
        self->f24 = *(s32 *)&st2[2];
        self->f28 = st2[3];
        self->f2C = *(s32 *)&st2[4];
        flag = 1;
        self->f18 = 9;
        break;
    case 6:
        EffectCreateByName_2e1020(st6, obj, D_00462648, -1);
        self->f1C = *(s16 *)&st6[0];
        self->f20 = *(s32 *)&st6[1];
        self->f24 = *(s32 *)&st6[2];
        self->f28 = st6[3];
        self->f2C = *(s32 *)&st6[4];
        flag = 1;
        self->f18 = 13;
        break;
    case 7:
        EffectCreateByName_2e1020(st7, obj, D_00462650, -1);
        self->f1C = *(s16 *)&st7[0];
        self->f20 = *(s32 *)&st7[1];
        self->f24 = *(s32 *)&st7[2];
        self->f28 = st7[3];
        self->f2C = *(s32 *)&st7[4];
        flag = 1;
        self->f18 = 14;
        break;
    case 10:
        self->f10 = 1;
        break;
    case 5:
        self->f18 = 12;
        self->f10 = 5;
        self->f10 = 1;
        break;
    case 8:
        FxStatusUpDownSpawnMaybe_2d7fd0(self->f14);
        self->f10 = 1;
        break;
    case 9:
        FxStatusUpDownSpawnMaybe_2d7f60(self->f14);
        self->f10 = 1;
        break;
    case 12:
        w = GetActionMgr_1fdb50();
        h = ActionMgrFindById_233b50(w, a1);
        if (h == 0) {
            return;
        }
        h = ActionMgrFindTableByScopeId_233c20(w, CharaGetActScopeId_214a70(h));
        if (h == 0) {
            return;
        }
        ActCfgTableRunEvntByName_21f680(h, a1, D_00462658);
        self->f10 = 1;
        break;
    }
    if (self->f18 > 0) {
        self->f1A = SoundNextPlayHandle_1b81c0();
    }
    if (flag == 0) {
        return;
    }
    self->f10 = 3;
    if (self->f20 == -1) {
        return;
    }
    EffectSetId_2e0100(obj, (f32 *)&self->f1C, self->f14);
    EffectSetName_2e01c0(obj, (f32 *)&self->f1C, D_00462668);
    EffectSetPos_2e0bb0(obj, (f32 *)&self->f1C, &mv);
}
