#pragma opt_propagation off
#include "types.h"
#include "event_vm.h"

extern void ObjRecClearFlags_1c3dc0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void ObjRecSetFlags_1c3e00(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 ScriptGetCodeAddr_249050(void);
extern s32 ScriptGetInt_2490f0(s32 arg0);
extern s32 EventCastFindKeyByName_24bb50(s32 arg0, s32 arg1);
extern s32 EventCastGetObjId_24c160(s32 arg0, s32 arg1);

s32 EvCmdCastShowMaybe_246400(s32 arg0) {
    s32 temp_16;
    s32 temp_16_2;

    arg0 += 8;
    temp_16 = (s32)((u8 *)gEventContext->player + 0x60);
    temp_16_2 = EventCastGetObjId_24c160(temp_16, EventCastFindKeyByName_24bb50(temp_16, ScriptGetCodeAddr_249050()));
    if (!(ScriptGetInt_2490f0(arg0) == 0)) {
        ObjRecClearFlags_1c3dc0(gEventContext->arg, 1, temp_16_2, 0x2000);
    } else {
        ObjRecSetFlags_1c3e00(gEventContext->arg, 1, temp_16_2, 0x2000);
    }
    return 1;
}
