#include "types.h"
#pragma opt_propagation off
extern s32 GetActionMgr_1fdb50(void);
extern void CharaInvokeInitBt2_212a70(s32);
extern void CharaInvokeInitBt1_212ad0(s32);
extern void CharaInvokeInitNrm_212b30(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptGetCodeAddr_249050(void);
extern s32 ScriptGetInt_2490f0(s32);
extern s32 EventCastFindKeyByName_24bb50(s32, s32);
extern s32 EventCastGetObjId_24c160(s32, s32);
extern void *gEventContext;

s32 EvCmdCharaInvokeInit_244180(s32 arg0)
{
    s32 c;
    s32 id;
    s32 o;

    arg0 += 8;
    c = *(s32 *)((u8 *)gEventContext + 4) + 0x60;
    id = EventCastGetObjId_24c160(c, EventCastFindKeyByName_24bb50(c, ScriptGetCodeAddr_249050()));
    o = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
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
