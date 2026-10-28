/* rgp:protos */
#define RGP_SELF_EvCmdMesWinGetParam_265e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                            /* extern */
/*rgp*/                           /* extern */
/*rgp*/                              /* extern */
/*rgp*/                           /* extern */

s32 EvCmdMesWinGetParam_265e00(s64 *arg0) {
    u8 *t;
    s32 k;

    t = ((u8 *)MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0((s32)arg0++)));
    if (t == 0) {
        return 0;
    }
    k = ScriptGetInt_26a2a0((s32)arg0++);
    switch (k) {
    case 0:
        ScriptSetRefInt_26a1e0((s32)arg0, *(s8 *)(t + 0x1DED) != 0);
        break;
    case 1:
        ScriptSetRefInt_26a1e0((s32)arg0, *(s8 *)(t + 0x1C3A) != 0);
        break;
    case 3:
        ScriptSetRefInt_26a1e0((s32)arg0, ((signed char)MesWinIsActive_2774d0(t)));
        break;
    case 4:
        ScriptSetRefInt_26a1e0((s32)arg0++, *(s32 *)(t + 0x40));
        ScriptSetRefInt_26a1e0((s32)arg0, *(s32 *)(t + 0x44));
        break;
    default:
        return 0;
    }
    return 1;
}
