#include "types.h"

extern void *ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern s32 ScriptGetCodeAddr_249050(s32);
extern s32 ScriptGetInt_2490f0(s32 arg0);
extern s32 EventCastFindKeyByName_24bb50(s32 arg0, s32 arg1);
extern s32 EventCastGetObjId_24c160(s32 arg0, s32 arg1);
extern void *gEventContext;

s32 EvCmdCastSetClothSimEnabled_244580(s64 *arg0, s32 arg1)
{
    s32 temp_18;
    s32 temp_17;
    void *temp_2;

    temp_18 = *(s32 *)((u8 *)gEventContext + 0x0);
    temp_17 = *(s32 *)((u8 *)gEventContext + 0x4) + 0x60;
    if (arg1 == 2) {
        temp_2 = ObjRecGetLiveObject_1c4a90(temp_18, EventCastGetObjId_24c160(temp_17, EventCastFindKeyByName_24bb50(temp_17, ScriptGetCodeAddr_249050((s32)arg0++))));
        if (temp_2 == NULL) {
            return 0;
        }
        *(s32 *)((u8 *)temp_2 + 0x460) = ScriptGetInt_2490f0((s32)arg0);
        return 1;
    }
    return 0;
}
