#include "types.h"

s8 *ModelGetRootFrame_1511a0(s32);
void ObjRecSetFlag2_1c3e80(s32, s32, s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
void LoaderReleaseById_1cd340(s32, s32);
s32 LoaderGetStatus_1cd4f0(s32, s32);
void LoaderQueueAppendSeparator_1cd670(s32);
s32 LoaderRequestFile_1cd870(s32, s32, s32);
s16 *CharaResFindByCharaId_1f04f0(s32, s32);
s32 GetLoaderMgr_1f59d0(void);
s32 GetCurrentScene_1f5be0(void);
s32 GetCharaResMgr_1fdb60(void);
s32 EventCastFindKeyByName_24bb50(s8 *, s32);
void EventCastLoadPoll_24c230(s8 *, s32, s32);

static inline s8 *NEXT(s8 *self, s32 *pkey) {
    s8 *node = *(s8 **)(self + 4);
    s8 *p;
    if (node == NULL) {
        p = NULL;
    } else {
        *pkey = *(s32 *)(node + 0xC);
        p = node + 0x10;
        node = *(s8 **)(node + 0);
        *(s8 **)(self + 4) = node;
        if (node == NULL) {
            *(s32 *)(self + 8) = 1;
        }
    }
    return p;
}
static inline s32 INR(s32 x, s32 lo, s32 hi) { s32 b = x >= lo; if (b) b = x < hi; return b; }

s32 EventCastRequestLoad_24bc30(s8 *self, s32 arg1) {
    s16 *ent;
    s32 s3;
    s32 s2;
    s32 r;
    s32 id;
    s8 *p;
    s32 key;
    s8 *node;
    s32 idx;
    s32 ok;
    s8 *q;

    s3 = GetLoaderMgr_1f59d0();
    s2 = GetCurrentScene_1f5be0();
    id = EventCastFindKeyByName_24bb50(self, arg1);
    if (*(s8 **)(self + 4) != NULL) {
        ok = -1;
    } else {
        *(s8 **)(self + 4) = *(s8 **)(self + 0);
        *(s32 *)(self + 8) = 0;
        ok = 0;
    }
    if (ok != 0) {
        p = NULL;
    } else {
        while ((p = NEXT(self, &key)) != NULL) {
            if (id == key) break;
        }
        *(s8 **)(self + 4) = NULL;
        *(s32 *)(self + 8) = 0;
    }
    if (p == NULL) {
        return 0;
    }
    key = *(s32 *)(p + 0x10);
    if (INR(key, 11000, 12000) || INR(key, 12000, 14000)) {
        ent = CharaResFindByCharaId_1f04f0(GetCharaResMgr_1fdb60(), key);
        if (ent != NULL) {
            key = *ent;
            r = ObjRecGetLiveObject_1c4a90(s2, key);
            if (r != 0) {
                q = ModelGetRootFrame_1511a0(r);
                if (q != NULL && *(s32 *)(p + 0xD4) == 0) {
                    *(s32 *)(p + 0xD4) = *(s32 *)(q + 4);
                }
                *(s32 *)(p + 0x1C) = key;
                ObjRecSetFlag2_1c3e80(s2, 1, key);
                idx = *(s32 *)(self + 0x324);
                *(s32 *)(self + 0x324) = idx + 1;
                (*(s32 **)(self + 0x320))[idx] = id;
                LoaderReleaseById_1cd340(s3, *(s32 *)(p + 0x24));
                LoaderReleaseById_1cd340(s3, *(s32 *)(p + 0x38));
                *(s32 *)(p + 0x24) = -1;
                *(s32 *)(p + 0x38) = -1;
                return 1;
            }
        }
    } else if (INR(key, 16000, 17200)) {
        if (ObjRecGetLiveObject_1c4a90(s2, *(s32 *)(p + 0x14)) != 0) {
            key = *(s32 *)(p + 0x18);
            *(s32 *)(p + 0x1C) = key;
            ObjRecSetFlag2_1c3e80(s2, 1, key);
            idx = *(s32 *)(self + 0x324);
            *(s32 *)(self + 0x324) = idx + 1;
            (*(s32 **)(self + 0x320))[idx] = id;
            LoaderReleaseById_1cd340(s3, *(s32 *)(p + 0x24));
            LoaderReleaseById_1cd340(s3, *(s32 *)(p + 0x38));
            *(s32 *)(p + 0x24) = -1;
            *(s32 *)(p + 0x38) = -1;
            return 1;
        }
    }
    *(s32 *)(p + 0x10) = -1;
    switch (LoaderGetStatus_1cd4f0(s3, *(s32 *)(p + 0x24))) {
    case -1:
        r = LoaderRequestFile_1cd870(s3, *(s32 *)(p + 4), 0);
        if (r < 0) {
            return 0;
        }
        *(s32 *)(p + 0x24) = r;
        if (*(s32 *)(p + 0x34) != 0) {
            *(s32 *)(p + 0x38) = LoaderRequestFile_1cd870(s3, *(s32 *)(p + 0x34), 0);
        }
        LoaderQueueAppendSeparator_1cd670(s3);
        break;
    case 0:
    case 1:
        break;
    }
    idx = *(s32 *)(self + 0x324);
    *(s32 *)(self + 0x324) = idx + 1;
    (*(s32 **)(self + 0x320))[idx] = id;
    EventCastLoadPoll_24c230(self, s2, id);
    return 1;
}
