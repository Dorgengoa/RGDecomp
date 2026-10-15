#include "types.h"

extern u8 *ConstructNewArray_100710(void *, void *, void *, s32, s32);
extern s32 MemStackAllocAligned64_14da10(u8 *, s32);
extern void MemStackReturnToOwnerMaybe_14dad0(u8 *);
extern void MemStackHeapAlloc_14db10(u8 *, s32, s32, s32);
extern s32 MemStackHeapAllocBack_14dcf0(u8 *, s32);
extern s32 MemStackHeapAllocFront_14dd10(u8 *, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern s32 AlignUp_1cacf0(s32, s32);
extern void LoaderQueueAppendSeparator_1cd670(s32);
extern void MapEntryCtor_1df710(void);
extern void MapObjRequestLoad_1e0a10(u8 *, void *, s32, s32);
extern void MapObjReset_1e0b00(u8 *);
extern void MapEntryPlaySpinMotion_1e0be0(u8 *);
extern s32 MapEntryInitWithRec_1e1250(u8 *, u8 *, s32, s32);
extern s32 MapEntryCloneWithCardNode_1e12c0(u8 *, s32, s32);
extern s32 MapDataLoadRequest_1e6990(u8 *, u8 *, s32, s32, s32, s32);
extern s32 MapDataGetHeap_1e7850(u8 *);
extern s32 MapDataGetState_1e7a00(u8 *);
extern s32 MapDataHasFallenLeaves_1e7a40(u8 *);
extern s32 MapDataHasBarFire_1e7a50(u8 *);
extern s32 MapDataIsGenericTransporter_1e7a80(u8 *);
extern s32 MapDataIsMemRev_1e7b90(u8 *);
extern s32 MapDataGetHeapSize_1e7ba0(u8 *);
extern s16 MapDataGetId_1e7bd0(u8 *);
extern s32 MapDataGetFileName_1e7be0(u8 *);
extern s32 MapDataGetName_1e7bf0(u8 *);
extern s32 MapDataIsEnabled_1e7c20(u8 *);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 GetGateObj_1fdac0(void);
extern u8 *GetGameData_1fede0(void);
extern s32 GetEventObjMgr_2d1960(void);
extern void TargetRefGetLocalPosMaybe_2e6bf0(s32, f32 *);
extern f32 TargetRefGetRadius_2e7100(s32);
extern s32 EventObjMgrFindObjByName_2e9920(s32, s32, s32);
extern s32 EvObjGetTargetRef_2f9ca0(s32);
extern u8 *GroupFindSubEntryNth_425520(s32, s32, s32, s32);
extern u8 *GroupGetRecordById_425590(s32, s32);
extern u8 D_0045B3F0[];
extern u8 D_0045B408[];

typedef struct { u8 pad[0x74]; s32 x74; } WA;
typedef struct { u8 pad[4]; s16 h4; } WB;
typedef struct { u8 pad[8]; WA *p8; u8 padC[0xC]; WB *p18; } W;

s32 MapBlockLoadRequest_1df0d0(u8 *o, u8 *p, s32 a2, s32 a3, s32 cnt) {
    s32 data;
    s32 size;
    s32 num;
    u8 *e;
    u8 *arr;
    W *w;
    s32 i;
    u8 *it;
    s32 k;
    s32 id;
    u8 *obj;
    s32 h;
    s32 r;
    s16 g;
    s16 hh;
    s32 x;
    f32 buf[4];

    if (MapDataIsEnabled_1e7c20(o) == 0) {
        return 0;
    }
    if (MapDataGetState_1e7a00(o) == -1) {
        return 0;
    }
    if (MapDataGetState_1e7a00(o) != 0) {
        return 0;
    }
    if (p == 0 || a2 == 0) {
        return 0;
    }
    {
        u8 f = *(s32 *)(p + 0x28) != 0;
        if (f) {
            return 0;
        }
    }
    if (MapDataGetName_1e7bf0(o) == 0) {
        return 0;
    }
    if (MapDataGetFileName_1e7be0(o) == 0) {
        return 0;
    }
    data = 0;
    if (a3 == 1) {
        MemStackHeapAlloc_14db10(p, 2, 0, 0x40);
        size = *(s32 *)(p + 0x34) - *(s32 *)(p + 0x2C) - 4;
        data = MemStackAllocAligned64_14da10(p, size);
        MemStackReturnToOwnerMaybe_14dad0(p);
    } else {
        size = AlignUp_1cacf0(MapDataGetHeapSize_1e7ba0(o), 0x100);
        switch (MapDataIsMemRev_1e7b90(o)) {
        case 0:
            data = MemStackHeapAllocFront_14dd10(p, size);
            break;
        case 1:
            data = MemStackHeapAllocBack_14dcf0(p, size);
            break;
        }
    }
    if (MapDataLoadRequest_1e6990(o, p, a2, MapDataGetFileName_1e7be0(o), data, size) == 0) {
        return 0;
    }
    if (MapDataHasBarFire_1e7a50(o) != 0) {
        *(s16 *)(o + 0xCA) += 1;
    }
    if (MapDataHasFallenLeaves_1e7a40(o) != 0) {
        *(s16 *)(o + 0xCA) += 1;
    }
    num = *(s16 *)(o + 0xCA);
    if (num > 0) {
        *(u8 **)(o + 0xC4) = ConstructNewArray_100710(MemStackNew_14e1b0(num * 0x18 + 0x10, MapDataGetHeap_1e7850(o)), 0, 0, 0x18, num);
        arr = *(u8 **)(o + 0xC4);
        if (arr == 0) {
            return 0;
        }
        e = arr;
        if (MapDataHasBarFire_1e7a50(o) != 0) {
            MapObjReset_1e0b00(arr);
            MapObjRequestLoad_1e0a10(arr, D_0045B3F0, 0x2DA, 0);
            e += 0x18;
        }
        if (MapDataHasFallenLeaves_1e7a40(o) != 0) {
            MapObjReset_1e0b00(e);
            MapObjRequestLoad_1e0a10(e, D_0045B408, 0x2DA, 1);
        }
    }
    LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    if (cnt < 0) {
        w = (W *)GetGameData_1fede0();
        if (MapDataIsGenericTransporter_1e7a80(o) == 0) {
            *(s16 *)(o + 0xC8) = 0;
            i = 0;
            while ((g = MapDataGetId_1e7bd0(o), hh = w->p18->h4, x = w->p8->x74, (it = GroupFindSubEntryNth_425520(x, hh, g, i))) != 0) {
                i++;
                if (*(s32 *)(it + 0x40) & 1) {
                    *(s16 *)(o + 0xC8) += 1;
                }
            }
        } else {
            *(s16 *)(o + 0xC8) = 1;
        }
        num = *(s16 *)(o + 0xC8);
        if (num > 0) {
            arr = ConstructNewArray_100710(MemStackNew_14e1b0(num * 0x7A0 + 0x10, MapDataGetHeap_1e7850(o)), MapEntryCtor_1df710, 0, 0x7A0, num);
            *(u8 **)(o + 0xC0) = arr;
            if (arr == 0) {
                return 0;
            }
            if (MapDataIsGenericTransporter_1e7a80(o) == 0) {
                k = 0;
                i = 0;
                while (g = MapDataGetId_1e7bd0(o), hh = w->p18->h4, x = w->p8->x74, it = GroupFindSubEntryNth_425520(x, hh, g, i), it != 0) {
                    i++;
                    if (*(s32 *)(it + 0x40) & 1) {
                        id = GetGateObj_1fdac0();
                        if (MapEntryInitWithRec_1e1250(*(u8 **)(o + 0xC0) + k * 0x7A0, it, id, MapDataGetHeap_1e7850(o)) == 0) {
                            return 0;
                        }
                        k++;
                    }
                }
            } else {
                it = GroupGetRecordById_425590(w->p8->x74, 0x321);
                id = GetGateObj_1fdac0();
                if (MapEntryInitWithRec_1e1250(*(u8 **)(o + 0xC0), it, id, MapDataGetHeap_1e7850(o)) == 0) {
                    return 0;
                }
                {
                    u8 *p_ = (u8 *)buf;
                    u32 n_ = 0x10;
                    if (p_) {
                        while (n_) {
                            *p_ = 0;
                            n_--;
                            p_++;
                        }
                    }
                }
                h = GetEventObjMgr_2d1960();
                r = EventObjMgrFindObjByName_2e9920(h, MapDataGetFileName_1e7be0(o), 0xF);
                if (r != 0) {
                    h = EvObjGetTargetRef_2f9ca0(r);
                    TargetRefGetLocalPosMaybe_2e6bf0(h, buf);
                    buf[3] = TargetRefGetRadius_2e7100(h);
                }
                *(f32 *)(it + 0x20) = buf[0];
                *(f32 *)(it + 0x24) = buf[1] + *(f32 *)(o + 0x34);
                *(f32 *)(it + 0x28) = buf[2];
                *(f32 *)(it + 0x2C) = buf[3];
                *(s16 *)(it + 0x18) = MapDataGetId_1e7bd0(o);
                MapEntryPlaySpinMotion_1e0be0(*(u8 **)(o + 0xC0));
            }
        }
    } else {
        arr = ConstructNewArray_100710(MemStackNew_14e1b0(cnt * 0x7A0 + 0x10, MapDataGetHeap_1e7850(o)), MapEntryCtor_1df710, 0, 0x7A0, cnt);
        *(u8 **)(o + 0xC0) = arr;
        if (arr != 0) {
            *(s16 *)(o + 0xC8) = cnt;
            for (i = 0; i < *(s16 *)(o + 0xC8); i++) {
                id = GetGateObj_1fdac0();
                if (MapEntryCloneWithCardNode_1e12c0(*(u8 **)(o + 0xC0) + i * 0x7A0, id, MapDataGetHeap_1e7850(o)) == 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
