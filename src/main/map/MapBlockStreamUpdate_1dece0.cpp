#include "types.h"
#pragma opt_propagation off

struct Ent {
    u8 pad0[0x32];
    s16 h32;
    u8 pad34[0x3C - 0x34];
    s32 x3C;
};

struct Obj {
    u8 pad0[8];
    s32 x8;
    u8 padC[0x2C - 0xC];
    u32 flags;
    u8 pad30[0xC4 - 0x30];
    u8 *xC4;
    s16 padC8;
    s16 hCA;
};

extern "C" {
void Sprintf_1343b8(char *, const char *, s32);
void ObjRecSetFlag2_1c3e80(s32, s32, s32);
bool MapBlockRelease_1df030(Obj *, s32);
void MapObjLoadStep_1e0850(u8 *, s32);
bool MapObjIsLoaded_1e0a80(u8 *);
s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
Ent *MapDataFindObjByName_1e71d0(Obj *, char *);
void MapDataSetState_1e72c0(Obj *, s32);
s32 MapDataGetHeap_1e7850(Obj *);
s32 MapDataGetObjRecSlot_1e7860(Obj *);
s32 MapDataGetState_1e7a00(Obj *);
s32 MapDataGetId_1e7bd0(Obj *);
char *MapDataGetFileName_1e7be0(s32);
s32 MapDataGetName_1e7bf0(Obj *);
s32 MapDataIsEnabled_1e7c20(Obj *);
void MapAreaDataLoadPoll_1e8a10(s32);
s32 MapAreaDataIsLoadDone_1e8ba0(s32);
s32 MapAreaDataIsLoadOk_1e8be0(s32);
void MapDataLoadFailLogStubMaybe_1e9950(s32);
void MapDataNoDataLogStubMaybe_1e9980(s32);
s32 GetCurrentScene_1f5be0(void);
void EventNotifyAreaLoaded_1ffad0(s32);
s32 GetMapMgr_201a90(void);
s32 strlen(const char *);
void MapDataPlaceModelThunk_1e6dd0(Obj *, s32, f32);
extern char D_0045B3B0[];
extern char D_0045B3D0[];
}

extern "C" bool MapBlockStreamUpdate_1dece0(Obj *obj, s32 arg1, f32 farg) {
    char buf[32];
    Ent *e;
    s32 last;
    s32 m;
    bool ret;
    bool ok;
    u8 *p;
    char *name;
    s32 r;
    u32 f;
    s32 i;
    bool b;



    f = obj->flags;
    b = (f & 0x40) != 0;
    if (b) {
        f |= 0x80;
    } else {
        f &= ~0x80;
    }
    obj->flags = f;
    obj->flags &= ~2;
    obj->flags &= ~4;
    obj->flags &= ~0x40;
    ret = 0;
    if (MapDataIsEnabled_1e7c20(obj) == 0) {
        switch (MapDataGetState_1e7a00(obj)) {
        case 1:
        case 2:
        case 3:
            ret = MapBlockRelease_1df030(obj, 1) != 0;
            break;
        }
    } else {
    if (MapDataGetState_1e7a00(obj) != 1) {
        return 0;
    }
    if (obj->x8 == 0) {
        MapDataNoDataLogStubMaybe_1e9980(MapDataGetName_1e7bf0(obj));
        MapDataSetState_1e72c0(obj, -1);
        return 0;
    }
    MapAreaDataLoadPoll_1e8a10(obj->x8);
    p = obj->xC4;
    ok = 1;
    if (p != 0) {
        for (i = 0; i < obj->hCA; i++, p += 0x18) {
            MapObjLoadStep_1e0850(p, MapDataGetHeap_1e7850(obj));
            ok &= MapObjIsLoaded_1e0a80(p);
        }
    }
    if (MapAreaDataIsLoadDone_1e8ba0(obj->x8) != 0 && ok) {
        if (MapAreaDataIsLoadOk_1e8be0(obj->x8) != 0) {
            MapDataPlaceModelThunk_1e6dd0(obj, arg1, farg);
            MapDataSetState_1e72c0(obj, 2);
            ret = 1;
            EventNotifyAreaLoaded_1ffad0(MapDataGetId_1e7bd0(obj));
            m = GetCurrentScene_1f5be0();
            ObjRecSetFlag2_1c3e80(m, 2, MapDataGetObjRecSlot_1e7860(obj));
            if (MapDataGetId_1e7bd0(obj) >= 20000 && MapDataGetId_1e7bd0(obj) < 20101) {
                m = GetMapMgr_201a90();
                r = MapSlotsFindBlockById_1e49b0(m, MapDataGetId_1e7bd0(obj) + 1000, 0);
                if (r != 0) {
                    name = MapDataGetFileName_1e7be0(r);
                    if (name != 0) {
                        last = name[strlen(name) - 1];
                        Sprintf_1343b8(buf, D_0045B3B0, last);
                        e = MapDataFindObjByName_1e71d0(obj, buf);
                        if (e != 0) {
                            e->h32 = 1;
                            e->x3C &= ~1;
                        }
                        Sprintf_1343b8(buf, D_0045B3D0, last);
                        e = MapDataFindObjByName_1e71d0(obj, buf);
                        if (e != 0) {
                            e->h32 = 0;
                            e->x3C |= 1;
                        }
                    }
                }
            }
        } else {
            MapDataLoadFailLogStubMaybe_1e9950(MapDataGetName_1e7bf0(obj));
            MapBlockRelease_1df030(obj, 1);
            MapDataSetState_1e72c0(obj, -1);
        }
    }
    }
    return ret;
}
