/* rgp:protos */
#define RGP_SELF_ActDataCnct_23b440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                         /* extern */
/*rgp*/                           /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                    /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                                 /* extern */
extern s32 D_00481EEC;

s32 ActDataCnct_23b440(s32 arg0, s32 arg1)
{
    s32 h;
    s32 *e;
    f32 f;

    if (arg1 != 1 && arg1 != 2) {
        return 0;
    }
    h = ActCfgGetCurTable_23ff20();
    if (h == 0) {
        return 1;
    }
    if (ActDataGetCnctList_225d00(h) == 0 || ((short)ActDataGetCnctCount_225cd0(h)) >= 0x20) {
        return 1;
    }
    e = (s32 *)(ActDataGetCnctList_225d00(h) + ((short)ActDataGetCnctCount_225cd0(h)) * 8);
    if (arg1 == 2) {
        f = ScriptArgGetFloat_23fbc0(arg0 + 8);
    } else {
        f = 1.0f;
    }
    ActDataCnctInit_227550(e, ((s32)ActCfgTableFindCmndByName_222db0(D_00481EEC, ScriptArgGetStr_23fba0(arg0))), f);
    if (*e == 0) {
        return 1;
    }
    ActDataSetCnctCount_225ca0(h, ((short)ActDataGetCnctCount_225cd0(h)) + 1);
    return 1;
}
