#include "types.h"

extern void *GetGameData_1fede0(void);
extern void *GetMapMgr_201a90(void);
extern void *MapFindAreaSlotById_1e4cb0(void *a, s32 id);
extern void *MapAreaGetScript_1dced0(void *o);
extern void  MemStackReset_14d830(char *s);
extern void  SystemVmLoadScript_250ac0(void *a, s32 b, char *s);
extern s32   SystemVmCall_250a50(s32 n, void *a);
extern void  SetFieldControlActive_27bd30(s32 v);
extern void *GetInteractState_27a650(void);
extern void  CameraPushTwoTarget_309c30(void *p);
extern void *GetActionMgr_1fdb50(void);
extern void *ActionMgrFindById_233b50(void *a, s32 id);
extern void  CharaResetBattleStateMaybe_212f20(void *a, s32 b);

extern char D_004D77B0[];
extern s8   D_0047E9A8;
extern s8   D_0048217C;

void CharaInteractRunAreaScriptMaybe_27a750(void *self)
{
    void *w;
    u8 *ctx;
    void *p;
    void *r;
    s32 id;

    id = *(s16 *)(*(u8 **)((u8 *)GetGameData_1fede0() + 0x18) + 0xA);
    r = MapFindAreaSlotById_1e4cb0(GetMapMgr_201a90(), id);
    if (r == 0) {
        return;
    }
    w = MapAreaGetScript_1dced0(r);
    if (w == 0) {
        return;
    }
    MemStackReset_14d830(D_004D77B0);
    SystemVmLoadScript_250ac0(w, 0, D_004D77B0);
    if (SystemVmCall_250a50(0x12C, self) == 0) {
        SetFieldControlActive_27bd30(1);
        D_0048217C = 3;
    } else {
        D_0047E9A8 = 0;
        *(s16 *)((u8 *)self + 0x58B4) = 0;
        *(s16 *)((u8 *)self + 0x58B6) = 0;
        CameraPushTwoTarget_309c30(GetInteractState_27a650());
        D_0048217C = 1;
        SetFieldControlActive_27bd30(0);
        ctx = (u8 *)GetGameData_1fede0();
        p = ActionMgrFindById_233b50(GetActionMgr_1fdb50(),
                         *(s16 *)(*(u8 **)(ctx + 0x18) + 0x18E));
        if (p != 0) {
            *(s32 *)((u8 *)p + 0xA44) |= 0x08000000;
            *(s32 *)((u8 *)p + 0xA44) |= 0x10000000;
            CharaResetBattleStateMaybe_212f20(p, 0);
        }
    }
}
