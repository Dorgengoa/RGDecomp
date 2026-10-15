#include "types.h"

typedef struct Lst {
    s16 x0;
    s16 x2;
    u8 pad4[0x4];
} Lst;

typedef struct Slot {
    s16 x0;
    s16 x2;
} Slot;

typedef struct Grp {
    u8 pad[0x1CC];
} Grp;

typedef struct Btl {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s8 xA;
    s8 xB;
    u8 xC[0x20];
    s16 x2C;
    s16 x2E;
    u8 pad30[0x30];
    s32 x60;
    u8 x64[0x4];
    u8 x68[0x78];
    u8 xE0[0x17D0];
    u8 x18B0[0x38];
    u8 x18E8[0x40];
    Grp x1928[4];
    u8 x2058[0x54];
    s16 x20AC;
    s16 x20AE;
    u8 x20B0[0xA4];
    u8 x2154[0xA4];
    u8 x21F8[0x10];
} Btl;

#define B8(o) ((u8 *)(b) + (o))
#define S16(o) (*(s16 *)((u8 *)(b) + (o)))

extern "C" {
extern bool MapAreaTick_1d9a20(void *);
extern s32 MapAreaReleaseBlockById_1d9d70(s32, s32, s32);
extern s32 MapAreaUnloadShareById_1d9ea0(s32, s32, s32);
extern s32 MapAreaLoadBlockById_1da210(s32, s32, s32, s32);
extern s32 MapAreaLoadShareById_1da320(s32, s32, s32, s32);
extern s32 MapAreaHasActiveBlockId_1dbff0(void *, s32);
extern s32 MapAreaGetActiveBlockCount_1dc0b0(void *);
extern s32 *MapAreaGetActiveBlockList_1dc0c0(void *);
extern s32 MapAreaGetActiveShareCount_1dc350(void *);
extern s32 *MapAreaGetActiveShareList_1dc360(void *);
extern s32 MapAreaFindBlockById_1dc760(void *, s32);
extern s32 MapBlockGetShareId_1e0080(s32);
extern s32 MapAreaReleaseById_1e2e00(Btl *, s32, s32);
extern s32 MapAreaSlotLoadById_1e3120(Btl *, s32, s32, void *, s32);
extern s32 MapMgrSkyLoadById_1e31f0(Btl *, s32);
extern void MapShareIdListClear_1e32f0(Btl *);
extern void MapAreaIdListClear_1e3300(Btl *);
extern void MapBlockIdListAdd_1e3320(Btl *, s32);
extern void MapShareIdListAdd_1e3330(Btl *, s32);
extern void MapAreaIdListAdd_1e3340(Btl *, s32);
extern s32 MapBlockIdListFind_1e3350(Btl *, s32);
extern s32 MapShareIdListFind_1e3360(Btl *, s32);
extern s32 MapAreaIdListFind_1e3370(Btl *, s32);
extern Slot *MapIdListFindByType_1e3380(Btl *, s32, s32);
extern void MapAlignAreaToAreaNode_1e3fb0(Btl *, void *);
extern s32 MapSlotsFindBlockById_1e49b0(Btl *, s32, s32 *);
extern s32 MapSlotsFindShareById_1e4a50(Btl *, s32, s32 *);
extern s32 MapSlotsFindById_1e4b90(Btl *, s32, s32 *);
extern s32 MapFindAreaSlotById_1e4cb0(Btl *, s32);
extern s32 MapMgrGetHeap_1e5810(Btl *);
extern s32 MapIdListCount_1e5a40(void *);
extern Lst *MapIdListGetEntries_1e5a70(void *);
extern void MapPendingLoadReset_1e5b40(void *);
extern void MapEnvSlotsInit_1e5f40(void *);
extern void MapSkyLoadPoll_1e6020(void *);
extern s32 MapSkyGetState_1e6350(void *);
extern bool MapDataStreamUpdate_1e6440(void *);
extern void MapDataSetState_1e72c0(s32, s32);
extern s32 MapDataIsLoadedOrUnloading_1e7980(s32);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 MapDataGetState_1e7a00(s32);
extern s32 MapDataGetId_1e7bd0(s32);
extern s32 MapDataIsEnabled_1e7c20(s32);
extern s32 GetGameData_1fede0(void);
extern void MapCaptionLoadStep_33f700(void *);
extern void WarpMenuLoadStep_39db50(void *);
extern u8 D_0045B488[];
}

extern "C" bool MapMgrLoadStep_1e1c50(Btl *b) {
    Lst *lstA;
    s32 iA;
    Lst *lstB;
    Lst *lstC;
    s32 p3;
    s32 p4;
    s32 p5;
    s32 p6;
    bool changed;
    bool a1f;
    bool a2f;
    s32 c;
    Grp *e;
    s32 i;
    s32 k;
    Lst *lst;
    s32 n;
    s32 j;
    s32 *arr;
    s32 m;
    s32 st;
    Slot *s;
    s16 v;
    s32 w;
    bool r;
    bool res;
    Grp *e2;
    s32 *arr2;
    s32 i2;

    b->x60 &= ~0x10;
    WarpMenuLoadStep_39db50(b->x18B0);
    MapCaptionLoadStep_33f700(b->x18E8);
    changed = false;
    MapShareIdListClear_1e32f0(b);
    MapAreaIdListClear_1e3300(b);
    MapAreaIdListAdd_1e3340(b, b->x2);
    MapAreaIdListAdd_1e3340(b, b->x4);
    MapAreaIdListAdd_1e3340(b, b->x6);
    MapAreaIdListAdd_1e3340(b, b->x8);
    a1f = false;
    a2f = false;
    c = MapFindAreaSlotById_1e4cb0(b, b->x2);
    if (c != 0 && MapDataIsLoaded_1e79d0(c) != 0) {
        a1f = true;
    }
    c = MapFindAreaSlotById_1e4cb0(b, b->x4);
    if (c != 0 && MapDataIsLoaded_1e79d0(c) != 0) {
        a2f = true;
    }
    for (e = &b->x1928[0], i = 0; i < 4; i++, e++) {
        if (MapAreaIdListFind_1e3370(b, MapDataGetId_1e7bd0((s32)e)) != 0) {
            if (MapDataGetState_1e7a00((s32)e) == 3) {
                MapDataSetState_1e72c0((s32)e, 2);
                changed = true;
            }
        } else if (MapAreaReleaseById_1e2e00(b, MapDataGetId_1e7bd0((s32)e), 0) != 0) {
            changed = true;
        }
    }
    if (!(b->x60 & 8) && MapAreaHasActiveBlockId_1dbff0(&b->x1928[0], b->x2C) != 0) {
        k = MapAreaFindBlockById_1dc760(&b->x1928[1], b->x2E);
        if (k != 0 && MapDataIsEnabled_1e7c20(k) != 0) {
            MapBlockIdListAdd_1e3320(b, MapDataGetId_1e7bd0(k));
        }
    }
    lst = MapIdListGetEntries_1e5a70(b->x21F8);
    n = MapIdListCount_1e5a40(b->x21F8);
    for (i = 0; i < n; i++, lst++) {
        k = MapSlotsFindBlockById_1e49b0(b, lst->x0, 0);
        if (k != 0) {
            MapShareIdListAdd_1e3330(b, MapBlockGetShareId_1e0080(k));
        }
    }
    for (e2 = &b->x1928[0], j = 0; j < 4; j++, e2++) {
        arr = MapAreaGetActiveBlockList_1dc0c0(e2);
        m = MapAreaGetActiveBlockCount_1dc0b0(e2);
        for (i = 0; i < m; i++, arr++) {
            if (*arr == 0) {
                continue;
            }
            if (MapBlockIdListFind_1e3350(b, MapDataGetId_1e7bd0(*arr)) != 0) {
                if (MapDataGetState_1e7a00(*arr) == 3) {
                    MapDataSetState_1e72c0(*arr, 2);
                    changed = true;
                }
            } else if (MapAreaReleaseBlockById_1d9d70((s32)e2, MapDataGetId_1e7bd0(*arr), (b->x60 & 8) != 0) != 0) {
                changed = true;
            } else if (MapDataIsLoadedOrUnloading_1e7980(*arr) != 0) {
                MapBlockIdListAdd_1e3320(b, MapDataGetId_1e7bd0(*arr));
                MapShareIdListAdd_1e3330(b, MapBlockGetShareId_1e0080(*arr));
            }
        }
        arr2 = MapAreaGetActiveShareList_1dc360(e2);
        m = MapAreaGetActiveShareCount_1dc350(e2);
        for (i2 = 0; i2 < m; i2++, arr2++) {
            if (*arr2 == 0) {
                continue;
            }
            if (MapShareIdListFind_1e3360(b, MapDataGetId_1e7bd0(*arr2)) != 0) {
                if (MapDataGetState_1e7a00(*arr2) == 3) {
                    MapDataSetState_1e72c0(*arr2, 2);
                    changed = true;
                }
            } else if (MapAreaUnloadShareById_1d9ea0((s32)e2, MapDataGetId_1e7bd0(*arr2), (b->x60 & 8) != 0) != 0) {
                changed = true;
            }
        }
    }
    st = b->x20AE;
    if (st == 1) {
        if (MapSkyGetState_1e6350(b->xE0) != 1) {
            MapPendingLoadReset_1e5b40(&b->x20AC);
        }
    } else {
        s = MapIdListFindByType_1e3380(b, b->x20AC, st);
        if (s != 0) {
            s->x2 = -1;
            k = MapSlotsFindById_1e4b90(b, b->x20AC, 0);
            if (k != 0) {
                v = MapDataGetState_1e7a00(k);
                s->x2 = v;
                if (v != 1) {
                    MapPendingLoadReset_1e5b40(&b->x20AC);
                }
            }
        } else {
            switch (b->x20AE) {
            case 2:
                if (MapAreaReleaseById_1e2e00(b, b->x20AC, (b->x60 & 8) != 0) != 0) {
                    changed = true;
                }
                break;
            case 3:
                k = MapSlotsFindShareById_1e4a50(b, b->x20AC, &p3);
                if (k != 0 && p3 != 0 && MapAreaUnloadShareById_1d9ea0(p3, MapDataGetId_1e7bd0(k), (b->x60 & 8) != 0) != 0) {
                    changed = true;
                }
                break;
            case 4:
                k = MapSlotsFindBlockById_1e49b0(b, b->x20AC, &p4);
                if (k != 0 && p4 != 0 && MapAreaReleaseBlockById_1d9d70(p4, MapDataGetId_1e7bd0(k), (b->x60 & 8) != 0) != 0) {
                    changed = true;
                }
                break;
            }
            MapPendingLoadReset_1e5b40(&b->x20AC);
        }
    }
    if (b->x20AC < 0 && MapMgrSkyLoadById_1e31f0(b, b->x0) != 0) {
        b->x20AC = 0;
        b->x20AE = 1;
    }
    lstA = MapIdListGetEntries_1e5a70(b->x20B0);
    n = MapIdListCount_1e5a40(b->x20B0);
    for (iA = 0; iA < n; iA++, lstA++) {
        w = -1;
        if (lstA->x0 == b->x2) {
            w = 0;
        }
        if (lstA->x0 == b->x4) {
            w = 1;
        }
        if (lstA->x0 == b->x6) {
            w = 2;
        }
        if (lstA->x0 == b->x8) {
            w = 3;
        }
        c = MapFindAreaSlotById_1e4cb0(b, lstA->x0);
        if (c != 0) {
            lstA->x2 = MapDataGetState_1e7a00(c);
        } else if (!(b->x60 & 1) && b->x20AC < 0) {
            lstA->x2 = 0;
            if (MapAreaSlotLoadById_1e3120(b, w, lstA->x0, D_0045B488, 0) != 0) {
                b->x20AC = lstA->x0;
                b->x20AE = 2;
            } else {
                b->x60 &= ~0x10;
            }
        }
    }
    lstB = MapIdListGetEntries_1e5a70(b->x2154);
    n = MapIdListCount_1e5a40(b->x2154);
    for (i = 0; i < n; i++, lstB++) {
        k = MapSlotsFindShareById_1e4a50(b, lstB->x0, &p5);
        lstB->x2 = 0;
        if (k != 0) {
            lstB->x2 = MapDataGetState_1e7a00(k);
        }
        if (!(b->x60 & 1) && b->x20AC < 0 && k != 0 && lstB->x2 == 0) {
            if (MapAreaLoadShareById_1da320(p5, MapMgrGetHeap_1e5810(b), lstB->x0, 0) != 0) {
                b->x20AC = lstB->x0;
                b->x20AE = 3;
            } else {
                b->x60 &= ~0x10;
            }
        }
    }
    GetGameData_1fede0();
    lstC = MapIdListGetEntries_1e5a70(b->x21F8);
    n = MapIdListCount_1e5a40(b->x21F8);
    for (i = 0; i < n; i++, lstC++) {
        k = MapSlotsFindBlockById_1e49b0(b, lstC->x0, &p6);
        lstC->x2 = 0;
        if (k != 0) {
            lstC->x2 = MapDataGetState_1e7a00(k);
        }
        if (!(b->x60 & 1) && b->x20AC < 0 && k != 0 && lstC->x2 == 0) {
            c = MapSlotsFindShareById_1e4a50(b, MapBlockGetShareId_1e0080(k), 0);
            if (c == 0 || MapDataIsLoaded_1e79d0(c) != 0) {
                if (MapAreaLoadBlockById_1da210(p6, MapMgrGetHeap_1e5810(b), lstC->x0, 0) != 0) {
                    b->x20AC = lstC->x0;
                    b->x20AE = 4;
                } else {
                    b->x60 &= ~0x10;
                }
            }
        }
    }
    MapSkyLoadPoll_1e6020(b->xE0);
    for (e = &b->x1928[0], i = 0; i < 4; i++, e++) {
        changed |= MapAreaTick_1d9a20(e);
    }
    r = MapDataStreamUpdate_1e6440(b->x2058);
    b->xA = 0;
    b->xB = 0;
    res = changed | r;
    c = MapFindAreaSlotById_1e4cb0(b, b->x2);
    if (c != 0 && MapDataIsLoaded_1e79d0(c) != 0) {
        b->xA = 1;
    }
    c = MapFindAreaSlotById_1e4cb0(b, b->x4);
    if (c != 0 && MapDataIsLoaded_1e79d0(c) != 0) {
        b->xB = 1;
    }
    if (b->xA != 0 && b->xB != 0 && (!a1f || !a2f)) {
        MapAlignAreaToAreaNode_1e3fb0(b, b->xC);
        if (!a1f) {
            MapEnvSlotsInit_1e5f40(b->x68);
        }
    }
    return res;
}
