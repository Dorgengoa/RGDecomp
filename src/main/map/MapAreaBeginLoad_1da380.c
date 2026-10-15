#include "types.h"

typedef struct Obj {
    u8 pad0[4];
    s32 f4;
    u8 pad8[0x24];
    s32 f2C;
    u8 pad30[0x78];
    u8 subA8[0x3C];
    s16 fE4;
} Obj;

typedef struct Mgr {
    u8 pad0[0x10];
    s32 f10;
} Mgr;

extern void LoaderQueueAppendSeparator_1cd670(s32);
extern void MapAreaSetShuffleCount_1dcdb0(Obj *, s32);
extern s32 MapAreaGetFileStem_1dce70(Obj *);
extern s32 MapAreaGetRecTable_1dce90(Obj *);
extern s32 MapAreaRequestPac_1dd090(void *, s32, s32, s32);
extern void LoadHandleRelease_1dd160(void *);
extern void MapDataSetState_1e72c0(Obj *, s32);
extern void MapDataSetHeapSize_1e7470(Obj *, s32);
extern s32 MapDataGetState_1e7a00(Obj *);
extern s32 MapDataGetId_1e7bd0(Obj *);
extern s32 MapDataGetFileName_1e7be0(Obj *);
extern s32 MapDataGetName_1e7bf0(Obj *);
extern s32 MapDataIsEnabled_1e7c20(void);
extern s32 GetLoaderMgr_1f59d0(void);
extern Mgr *GetGameData_1fede0(void);
extern s32 StateFlagTest_3ccd70(s32, s32);

s32 MapAreaBeginLoad_1da380(Obj *obj, s32 arg1, s32 mode, s32 time)
{
    s32 a;
    s32 b;

    if (MapDataIsEnabled_1e7c20() == 0) {
        return 0;
    }
    if (MapDataGetState_1e7a00(obj) == -1) {
        return 0;
    }
    if (MapDataGetState_1e7a00(obj) != 0) {
        return 0;
    }
    LoadHandleRelease_1dd160(obj->subA8);
    if (arg1 == 0) {
        return 0;
    }
    if (MapAreaGetRecTable_1dce90(obj) == 0) {
        return 0;
    }
    if (MapDataGetName_1e7bf0(obj) == 0) {
        return 0;
    }
    if (MapDataGetFileName_1e7be0(obj) == 0) {
        return 0;
    }
    obj->f4 = arg1;
    obj->f2C &= ~0x200;
    switch (mode) {
    case 2:
        obj->fE4 = 7;
        break;
    case 0:
        obj->fE4 = 4;
        if (MapDataGetId_1e7bd0(obj) == 0x6A4) {
            obj->f2C |= 1;
            MapAreaSetShuffleCount_1dcdb0(obj, (StateFlagTest_3ccd70(GetGameData_1fede0()->f10, 0x7FD) & 0xFF) ? -1 : 100);
        }
        break;
    case 3:
        obj->fE4 = 8;
        break;
    default:
        obj->f2C |= 0x200;
        obj->fE4 = 6;
        break;
    }
    if (time > 0) {
        MapDataSetHeapSize_1e7470(obj, time);
    }
    if (mode != 3) {
        a = MapAreaGetRecTable_1dce90(obj);
        b = MapDataGetFileName_1e7be0(obj);
        if (MapAreaRequestPac_1dd090(obj->subA8, a, b, MapAreaGetFileStem_1dce70(obj)) == 0) {
            return 0;
        }
        LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    }
    MapDataSetState_1e72c0(obj, 1);
    return 1;
}
