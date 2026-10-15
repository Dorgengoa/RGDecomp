#include "types.h"

extern void *GetMapMgr_201a90(void);
extern void *MapFindAreaSlotById_1e4cb0(void *a, s32 id);
extern void *MapAreaGetScript_1dced0(void *o);
extern void  MemStackReset_14d830(char *s);
extern void  SystemVmLoadScript_250ac0(void *a, s32 b, char *s);
extern s32   SystemVmCall_250a50(s32 n, void *a);
extern void  SetFieldControlActive_27bd30(s32 v);
extern s32   SysModeMsgIsKeyCapWarpStartMaybe_27bc40(void);

extern char D_004D77B0[];
extern s8   D_0047E9A8;
extern s8   D_0048217C;
extern s32  D_00482174;
extern s8   D_00482184;

void MapAreaScriptRun_27a9e0(void *self, s32 n, s32 id)
{
    void *w;
    s32 v;
    void *r;

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
    if (SystemVmCall_250a50(n, self) == 0) {
        SetFieldControlActive_27bd30(1);
        D_0048217C = 3;
    } else {
        D_0047E9A8 = 0;
        SetFieldControlActive_27bd30(0);
        D_0048217C = 0;
        v = -0x20;
        if (SysModeMsgIsKeyCapWarpStartMaybe_27bc40() != 0) {
            v = 0;
        }
        *(s16 *)((u8 *)self + 0x58B4) = 0;
        *(s16 *)((u8 *)self + 0x58B6) = v;
        D_00482174 = 0;
        D_00482184 = 0;
    }
}
