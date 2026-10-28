/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

struct Obj001E6440 {
    u8 pad0[8];
    s32 unk8;
    u8 padc[0x2C - 0xC];
    u32 unk2C;

    bool isFlag(u32 m) { return (unk2C & m) != 0; }
    void setFlag(u32 m, bool on) { unk2C = on ? (unk2C | m) : (unk2C & ~m); }
    void clrFlag(u32 m) { unk2C &= ~m; }
};

extern "C" {
void ObjRecSetFlag2_1c3e80(s32, s32, s32);
s32 MapDataUnload_1e6690(Obj001E6440 *, s32);
void MapDataSetState_1e72c0(Obj001E6440 *, s32);
s32 MapDataGetObjRecSlot_1e7860(Obj001E6440 *);
s32 MapDataGetState_1e7a00(Obj001E6440 *);
s32 MapDataGetId_1e7bd0(Obj001E6440 *);
s32 MapDataGetName_1e7bf0(Obj001E6440 *);
s32 MapDataIsEnabled_1e7c20(Obj001E6440 *);
void MapAreaDataLoadPoll_1e8a10(s32);
s32 MapAreaDataIsLoadDone_1e8ba0(s32);
s32 MapAreaDataIsLoadOk_1e8be0(s32);
void MapDataLoadFailLogStubMaybe_1e9950(void);
void MapDataNoDataLogStubMaybe_1e9980(void);
s32 GetCurrentScene_1f5be0();
void EventNotifyAreaLoaded_1ffad0(s32);
}

extern "C" bool MapDataStreamUpdate_1e6440(Obj001E6440 *arg0)
{
    bool ret;
    s32 k;
    s32 w;

    arg0->setFlag(0x80, arg0->isFlag(0x40));
    arg0->clrFlag(2);
    arg0->clrFlag(4);
    ret = false;
    arg0->clrFlag(0x40);
    if (((unsigned char)MapDataIsEnabled_1e7c20(arg0)) == 0) {
        switch (((signed char)MapDataGetState_1e7a00(arg0))) {
        case 1:
        case 2:
        case 3:
            ret = (u8)MapDataUnload_1e6690(arg0, 1);
            break;
        }
    } else {
    if (((signed char)MapDataGetState_1e7a00(arg0)) != 1) {
        return false;
    }
    if (arg0->unk8 == 0) {
        ((void)(MapDataGetName_1e7bf0(arg0)), MapDataNoDataLogStubMaybe_1e9980());
        MapDataSetState_1e72c0(arg0, -1);
        return false;
    }
    MapAreaDataLoadPoll_1e8a10(arg0->unk8);
    if (((unsigned char)MapAreaDataIsLoadDone_1e8ba0(arg0->unk8)) != 0) {
        if (((unsigned char)MapAreaDataIsLoadOk_1e8be0(arg0->unk8)) != 0) {
            MapDataSetState_1e72c0(arg0, 2);
            ret = true;
            EventNotifyAreaLoaded_1ffad0(((short)MapDataGetId_1e7bd0(arg0)));
            w = GetCurrentScene_1f5be0();
            ObjRecSetFlag2_1c3e80(w, 2, MapDataGetObjRecSlot_1e7860(arg0));
        } else {
            ((void)(MapDataGetName_1e7bf0(arg0)), MapDataLoadFailLogStubMaybe_1e9950());
            MapDataUnload_1e6690(arg0, 1);
            MapDataSetState_1e72c0(arg0, -1);
        }
    }
    }
    return ret;
}
