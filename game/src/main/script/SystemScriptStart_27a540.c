/* rgp:protos */
#define RGP_SELF_SystemScriptStart_27a540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s8 D_0048217C;
extern u8 D_004D77B0[0x400];

void SystemScriptStart_27a540(void *self, s32 arg1, s32 arg2)
{
    s16 v;

    MemStackReset_14d830(&(*(u8 *)D_004D77B0));
    SystemVmLoadScript_250ac0(arg1, 0, &(*(u8 *)D_004D77B0));
    if (SystemVmCall_250a50(arg2, self, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) == 0) {
        SetFieldControlActive_27bd30(1);
        D_0048217C = 3;
    } else {
        SetFieldControlActive_27bd30(0);
        D_0048217C = 0;
        v = -0x20;
        if (SysModeMsgIsKeyCapWarpStartMaybe_27bc40() != 0) {
            v = 0;
        }
        *(s16 *)((u8 *)self + 0x58B4) = 0;
        *(s16 *)((u8 *)self + 0x58B6) = v;
    }
}
