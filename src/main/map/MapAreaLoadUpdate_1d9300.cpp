#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

typedef struct {
    V4 r[4];
} M4;

extern "C" {
void FrameCalcWorldMatrix_148ff0(s32, M4 *);
s32 FrameFindByName_149ed0(s32, s32);
s32 ModelGetRootFrame_1511a0(s32);
void ObjRecSetFlag2_1c3e80(s32, s32, s32);
void MatToRotPos_1cade0(V4 *, V4 *, M4 *);
s32 MapAreaStartLoad_1d8370(u8 *);
s32 MapAreaLoadTreasureBox_1d84d0(u8 *, s32);
s32 MapAreaCopySeqStb_1d8650(u8 *);
s32 MapAreaRunDoorScript_1d8740(u8 *);
s32 MapAreaRunDefScript_1d8830(u8 *);
s32 MapAreaCopyStb_1d8920(u8 *);
s32 MapAreaLoadMinimap_1d8a10(u8 *);
void MapAreaPollLoadEffects_1d8ba0(u8 *);
s32 MapAreaHeapAllocMax_1d8d20(u8 *);
s32 MapAreaHeapAllocAndClone_1d8e00(u8 *);
s32 MapAreaHeapAllocRest_1d8e50(u8 *);
s32 MapAreaHeapAlloc_1d8ef0(u8 *);
void MapAreaRelease_1d9ee0(u8 *, s32);
void MapAreaPlaceDefault_1da960(u8 *);
u8 *MapAreaFindBaseNode_1daa80(u8 *);
s32 MapAreaGetBlockCount_1dce20(u8 *);
u8 *MapAreaGetBlocks_1dce30(u8 *);
void MapDataSetState_1e72c0(u8 *, s32);
void MapDataSetOffsetRotY_1e73d0(u8 *, f32);
void MapDataSetOffsetPos_1e73f0(u8 *, V4 *);
s32 MapDataGetObjRecSlot_1e7860(u8 *);
s32 MapDataGetId_1e7bd0(u8 *);
s32 MapDataGetName_1e7bf0(u8 *);
void MapAreaDataLoadPoll_1e8a10(s32);
s32 MapAreaDataIsLoadDone_1e8ba0(s32);
s32 MapAreaDataIsLoadOk_1e8be0(s32);
u8 *MapAreaDataGetSceneCfg_1e8bf0(s32);
void MapDataLoadFailLogStubMaybe_1e9950(s32);
s32 MapAreaLoadDef_1ea080(u8 *);
s32 MapAreaRunDataScripts_1ead90(u8 *);
s32 GetCurrentScene_1f5be0(void);
void EventNotifyAreaLoaded_1ffad0(s32);
s32 GetMinimapMgr_201a70(void);
void MinimapMgrPresetExploredAll_321700(s32);
extern f32 D_0047DCA8;
extern f32 D_0047DCAC;
extern f32 D_0047E380;
extern f32 D_0047E384;
extern f32 D_0047E388;
extern f32 D_0047E38C;
extern f32 D_0047E390;
extern f32 D_0047E394;
extern f32 D_0047E398;
extern f32 D_0047E39C;
bool MapAreaLoadUpdate_1d9300(u8 *arg0);
}

#define ST (*(s16 *)(arg0 + 0xE4))

bool MapAreaLoadUpdate_1d9300(u8 *arg0)
{
    V4 b;
    V4 a;
    M4 m;
    bool ret;
    s32 r;
    s16 t;
    u8 *c;
    u8 *d;
    s32 h;
    s32 n;
    s32 i;
    s32 k;
    u8 *e;
    s32 s;

    if (ST == 0) {
        MapDataSetState_1e72c0(arg0, -1);
        return false;
    }
    ret = false;
    if (*(s32 *)(arg0 + 8) != 0) {
        MapAreaDataLoadPoll_1e8a10(*(s32 *)(arg0 + 8));
    }
    switch (ST) {
    case 4:
        r = MapAreaRunDataScripts_1ead90(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
            break;
        }
        if (*(s32 *)(arg0 + 0x2C) & 0x400) {
            ST = 6;
        } else {
            ST = 5;
        }
        MapAreaLoadUpdate_1d9300(arg0);
        break;
    case 5:
        r = MapAreaHeapAlloc_1d8ef0(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
        } else {
            ST = 9;
        }
        break;
    case 6:
        r = MapAreaHeapAllocRest_1d8e50(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
        } else {
            ST = 9;
        }
        break;
    case 7:
        r = MapAreaHeapAllocAndClone_1d8e00(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
        } else {
            ST = 0xA;
        }
        break;
    case 8:
        r = MapAreaHeapAllocMax_1d8d20(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
            break;
        }
        ST = 0x14;
        MapAreaLoadUpdate_1d9300(arg0);
        break;
    case 9:
        if (!(*(s32 *)(arg0 + 0x2C) & 0x400)) {
            r = MapAreaLoadDef_1ea080(arg0);
            if (r == 0) {
                break;
            }
            if (r == -1) {
                ST = 1;
            } else {
                ST = 0xA;
            }
        } else {
            ST = 0xA;
            MapAreaLoadUpdate_1d9300(arg0);
        }
        break;
    case 10:
        MapAreaPollLoadEffects_1d8ba0(arg0);
        ST = 0xB;
        MapAreaLoadUpdate_1d9300(arg0);
        break;
    case 11:
        r = MapAreaLoadMinimap_1d8a10(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
            break;
        }
        ST = 0xC;
        if (r == 1) {
            MapAreaLoadUpdate_1d9300(arg0);
        }
        break;
    case 12:
        r = MapAreaCopyStb_1d8920(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
            break;
        }
        ST = 0xD;
        if (r == 1) {
            MapAreaLoadUpdate_1d9300(arg0);
        }
        break;
    case 13:
        r = MapAreaCopySeqStb_1d8650(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
            break;
        }
        ST = 0xE;
        if (r == 1) {
            MapAreaLoadUpdate_1d9300(arg0);
        }
        break;
    case 14:
        r = MapAreaRunDefScript_1d8830(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
            break;
        }
        ST = 0xF;
        if (r == 1) {
            MapAreaLoadUpdate_1d9300(arg0);
        }
        break;
    case 15:
        r = MapAreaRunDoorScript_1d8740(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
            break;
        }
        ST = 0x10;
        if (r == 1) {
            MapAreaLoadUpdate_1d9300(arg0);
        }
        break;
    case 16:
    case 17:
    case 18:
    case 19:
        r = MapAreaLoadTreasureBox_1d84d0(arg0, ST - 0x10);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
            break;
        }
        t = ST + 1;
        ST = t;
        if (t >= 0x14) {
            ST = 0x14;
        }
        if (r == 1) {
            MapAreaLoadUpdate_1d9300(arg0);
        }
        break;
    case 20:
        r = MapAreaStartLoad_1d8370(arg0);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            ST = 1;
        } else {
            ST = 0x15;
        }
        break;
    case 21:
        if (MapAreaDataIsLoadDone_1e8ba0(*(s32 *)(arg0 + 8)) == 0) {
            break;
        }
        if (MapAreaDataIsLoadOk_1e8be0(*(s32 *)(arg0 + 8)) == 0) {
            ST = 1;
        } else {
            ST = 2;
        }
        break;
    }
    switch (ST) {
    case 2:
        c = MapAreaFindBaseNode_1daa80(arg0);
        if (c != 0) {
            d = MapAreaGetBlocks_1dce30(arg0);
            if (d != 0) {
                h = ModelGetRootFrame_1511a0(*(s32 *)(c + 0x6C));
                n = MapAreaGetBlockCount_1dce20(arg0);
                for (i = 0; i < n; i++, d += 0xCC) {
                    { f32 *p = (f32 *)&b; p[0] = D_0047E380; p[1] = D_0047E384; p[2] = D_0047E388; p[3] = D_0047E38C; p = (f32 *)&a; p[0] = D_0047E390; p[1] = D_0047E394; p[2] = D_0047E398; p[3] = D_0047E39C; }
                    k = FrameFindByName_149ed0(h, MapDataGetName_1e7bf0(d));
                    if (k != 0) {
                        FrameCalcWorldMatrix_148ff0(k, &m);
                        MatToRotPos_1cade0(&a, &b, &m);
                    }
                    MapDataSetOffsetPos_1e73f0(d, &b);
                    MapDataSetOffsetRotY_1e73d0(d, a.y);
                }
            }
        }
        e = MapAreaDataGetSceneCfg_1e8bf0(*(s32 *)(arg0 + 8));
        if (e != 0) {
            *(f32 *)(arg0 + 0xF8) = *(f32 *)(e + 0x198);
            if (MapDataGetId_1e7bd0(arg0) != 0x12C) {
                if (MapDataGetId_1e7bd0(arg0) == 0xC8) {
                    *(f32 *)(e + 0x198) = D_0047DCAC;
                } else {
                    *(f32 *)(e + 0x198) = D_0047DCA8;
                }
            }
        }
        MapAreaPlaceDefault_1da960(arg0);
        MapDataSetState_1e72c0(arg0, 2);
        ret = true;
        MinimapMgrPresetExploredAll_321700(GetMinimapMgr_201a70());
        EventNotifyAreaLoaded_1ffad0(MapDataGetId_1e7bd0(arg0));
        s = GetCurrentScene_1f5be0();
        ObjRecSetFlag2_1c3e80(s, 2, MapDataGetObjRecSlot_1e7860(arg0));
        break;
    case 1:
        MapDataLoadFailLogStubMaybe_1e9950(MapDataGetName_1e7bf0(arg0));
        MapAreaRelease_1d9ee0(arg0, 1);
        MapDataSetState_1e72c0(arg0, -1);
        break;
    }
    if (ST != 1 && ST != 2) {
        return ret;
    }
    ST = 0;
    return ret;
}
