#include "types.h"
#pragma opt_propagation off

struct Obj001ECC20 {
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
s32 MapDataUnloadThunk_1e6690(Obj001ECC20 *, s32);
void MapDataPlaceModelThunk2_1e6dd0(Obj001ECC20 *, s32, f32);
void MapDataSetState_1e72c0(Obj001ECC20 *, s32);
s32 MapDataGetObjRecSlot_1e7860(Obj001ECC20 *);
s32 MapDataGetState_1e7a00(Obj001ECC20 *);
s32 MapDataGetId_1e7bd0(Obj001ECC20 *);
s32 MapDataGetName_1e7bf0(Obj001ECC20 *);
s32 MapDataIsEnabled_1e7c20(Obj001ECC20 *);
void MapAreaDataLoadPoll_1e8a10(s32);
s32 MapAreaDataIsLoadDone_1e8ba0(s32);
s32 MapAreaDataIsLoadOk_1e8be0(s32);
void MapDataLoadFailLogStubMaybe_1e9950(s32);
void MapDataNoDataLogStubMaybe_1e9980(s32);
s32 GetCurrentScene_1f5be0();
void EventNotifyAreaLoaded_1ffad0(s32);
}

extern "C" bool MapShareStreamUpdate_1ecc20(Obj001ECC20 *arg0, s32 arg1, f32 arg2)
{
    bool ret;
    s32 k;
    s32 w;

    arg0->setFlag(0x80, arg0->isFlag(0x40));
    arg0->clrFlag(2);
    arg0->clrFlag(4);
    ret = false;
    arg0->clrFlag(0x40);
    if (MapDataIsEnabled_1e7c20(arg0) == 0) {
        switch (MapDataGetState_1e7a00(arg0)) {
        case 1:
        case 2:
        case 3:
            ret = (u8)MapDataUnloadThunk_1e6690(arg0, 1);
            break;
        }
    } else {
    if (MapDataGetState_1e7a00(arg0) != 1) {
        return false;
    }
    if (arg0->unk8 == 0) {
        MapDataNoDataLogStubMaybe_1e9980(MapDataGetName_1e7bf0(arg0));
        MapDataSetState_1e72c0(arg0, -1);
        return false;
    }
    MapAreaDataLoadPoll_1e8a10(arg0->unk8);
    if (MapAreaDataIsLoadDone_1e8ba0(arg0->unk8) != 0) {
        if (MapAreaDataIsLoadOk_1e8be0(arg0->unk8) != 0) {
            MapDataPlaceModelThunk2_1e6dd0(arg0, arg1, arg2);
            MapDataSetState_1e72c0(arg0, 2);
            ret = true;
            EventNotifyAreaLoaded_1ffad0(MapDataGetId_1e7bd0(arg0));
            w = GetCurrentScene_1f5be0();
            ObjRecSetFlag2_1c3e80(w, 2, MapDataGetObjRecSlot_1e7860(arg0));
        } else {
            MapDataLoadFailLogStubMaybe_1e9950(MapDataGetName_1e7bf0(arg0));
            MapDataUnloadThunk_1e6690(arg0, 1);
            MapDataSetState_1e72c0(arg0, -1);
        }
    }
    }
    return ret;
}
