/* rgp:protos */
#define RGP_SELF_EvCmdCharaInvokeInit_244180 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *gEventContext;

s32 EvCmdCharaInvokeInit_244180(s32 arg0)
{ __typeof__(arg0) rgp_entry_arg0 = arg0;
    s32 c;
    s32 id;
    s32 o;

    arg0 += 8;
    c = *(s32 *)((u8 *)gEventContext + 4) + 0x60;
    id = EventCastGetObjId_24c160(c, EventCastFindKeyByName_24bb50(c, ScriptGetCodeAddr_249050((void *)rgp_entry_arg0)), 0);
    o = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), id));
    if (o == 0) {
        return 1;
    }
    switch (ScriptGetInt_2490f0(arg0)) {
    case 0:
        CharaInvokeInitNrm_212b30(o);
        break;
    case 1:
        CharaInvokeInitBt1_212ad0(o);
        break;
    case 2:
        CharaInvokeInitBt2_212a70(o);
        break;
    }
    return 1;
}
