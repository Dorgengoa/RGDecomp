#include "types.h"

typedef struct {
    u8 pad0[0xD0];
    u32 unkD0;
} Obj0010;

extern s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
extern s32 EvDoorObjGetState_304040(Obj0010 *);
extern s32 EvObjLiftGetPlayState_336120(Obj0010 *);
extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);

s32 EventObjMgrDoorsLiftsIdle_2e8c60(s32 arg0)
{
    u32 temp_3;
    s32 var_17;
    Obj0010 *temp_16;

    var_17 = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(arg0, 9));
    while (var_17 != 0) {
        temp_16 = (Obj0010 *)(var_17 + 0x10);
        var_17 = DListGetNext_42eb30(var_17);
        temp_3 = temp_16->unkD0;
        if ((((temp_3 & 0x80000000) != 0) ^ 1) && (temp_3 & 0x02000000) && (EvDoorObjGetState_304040(temp_16) != 0)) {
            return 0;
        }
    }
    var_17 = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(arg0, 4));
    while (var_17 != 0) {
        temp_16 = (Obj0010 *)(var_17 + 0x10);
        var_17 = DListGetNext_42eb30(var_17);
        temp_3 = temp_16->unkD0;
        if ((((temp_3 & 0x80000000) != 0) ^ 1) && (temp_3 & 0x02000000) && (EvObjLiftGetPlayState_336120(temp_16) != 0)) {
            return 0;
        }
    }
    return 1;
}
