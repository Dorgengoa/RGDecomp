/* rgp:protos */
#define RGP_SELF_ScriptFnSysMsgExitMaybe_3d75d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Msg {
    s16 x0;
    s8 x2;
    u8 x3;
    s16 x4;
    s16 x6;
    u8 pad[0x68];
} Msg;

extern void SysMsgPostMaybe_1c3560(s32, Msg *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnSysMsgExitMaybe_3d75d0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    Msg m __attribute__((aligned(16)));

    if (arg0 == 0 || (VariantSetS32_36f040(arg0, 0, 1), D_00483960 == 0) || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    ScriptFnPushLoadingMode_3d7740(arg0);
    ScriptFnIsSysReady_3d76d0(arg0);
    SysMsgInit_1c69e0(&m);
    m.x0 = 0;
    m.x2 = 0;
    m.x6 = 0;
    m.x4 = 0;
    if (arg3 != 0 && arg2 > 0) {
        m.x4 = VariantGetS32_36fb30(arg3);
    }
    SysMsgPostMaybe_1c3560(1, &m);
    SetGameExitRequest_1f57d0(1);
    VariantSetS32_36f040(arg0, 1, 1);
}
