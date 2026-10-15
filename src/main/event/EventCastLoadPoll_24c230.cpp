#include "types.h"

typedef struct Ent4c {
    u8 pad0[4];
    char *name;
    s32 type;
    s32 mC;
    u8 pad10[0xC];
    s32 m1C;
    s32 m20;
    s32 m24;
    u8 pad28[0x10];
    s32 m38;
    u8 pad3C[8];
    s32 m44;
    f32 m48;
    s32 m4C;
} Ent4c;

typedef struct Node4c {
    struct Node4c *next;
    u8 pad4[8];
    s32 key;
    Ent4c data;
} Node4c;

typedef struct It4c {
    Node4c *head;
    Node4c *cur;
    s32 done;
    u8 padC[0x320 - 0xC];
    s32 *ids;
    s32 nids;
    u8 pad328[4];
    s32 m32C;
} It4c;

class Obj4c {
public:
    u8 pad0[0x1B0];
    virtual void u21_0();
    virtual void u21_1();
    virtual void u21_2();
    virtual void u21_3();
    virtual void u21_4();
    virtual void u21_5();
    virtual void u21_6();
    virtual void u21_7();
    virtual void u21_8();
    virtual void u21_9();
    virtual void u21_10();
    virtual void u21_11();
    virtual void u21_12();
    virtual void u21_13();
    virtual void u21_14();
    virtual void u21_15();
    virtual void u21_16();
    virtual void u21_17();
    virtual void u21_18();
    virtual void u21_19();
    virtual void u21_20();
    virtual void v5C();
};

typedef struct Chr4c {
    u8 pad0[0x4F0];
    s32 m4F0;
    u8 pad4F4[8];
    s32 m4FC;
    u8 pad500[0x18];
    s32 m518;
    u8 pad51C[0x18];
    s32 m534;
} Chr4c;

extern "C" {
Obj4c *MemStackNew_14e230(s32, s32);
void ModelObjExCopy_1aff40(s32, Obj4c *, s32);
void SoundBankRelease_1bb6e0(s32);
void ObjRecSetValue_1c3d60(s32, s32, s32, s32);
void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
void ObjRecClearFlag2_1c3e40(s32, s32, s32);
void ObjRecSetFlag2_1c3e80(s32, s32, s32);
s32 RecStackGetSlot_1c4330(s32, s32);
void ModelObjExCtor_1c4920(Obj4c *);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
void LoaderReleaseById_1cd340(s32 *, s32);
s32 LoaderGetData_1cd490(s32 *, s32, s32 *);
s32 LoaderGetStatus_1cd4f0(s32 *, s32);
void ParamTableSetAlpha_1cfb10(s32, s32, f32);
f32 ParamTableGetAlpha_1cfb40(s32, s32);
void GameSceneObjBindMaybe_1cfcd0(s32, s32, Obj4c *, s32);
s32 GameSceneSoundSlot6LoadBank_1d06d0(s32, s32);
s32 GameSceneSoundSlot6StartFromData_1d06e0(s32, s32);
s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
void GameSceneSoundSlot6Free_1d0850(s32);
s32 *GetLoaderMgr_1f59d0(void);
void EventCastSetEnabledMaybe_24aa40(It4c *, s32, s32, s32);
s32 EventCastRegisterImArchive_24b260(It4c *, s32, s32, s32, s32, s32, s32);
s32 EventCastObjLoadInfoCfgModels_24b360(It4c *, s32, s32, s32, s32, s32, void *);
s32 EventCastObjLoadInfoCfg_24b510(It4c *, s32, s32, s32, s32, s32, void *);
s32 EventCastCreateObj_24b8c0(It4c *, s32, s32, s32, s32, s32, void *, s32);
s32 EventCastFindKeyByName_24bb50(It4c *, s32);
s32 EventCastGetObjId_24c160(It4c *, s32);
void EventSoundBankHandleSet_24fca0(s32, s32);
s32 EventCastDataGroupIdAlloc_2503a0(s32);
s32 EventCastFindFreeObjSlot_2503e0(s32);
s32 EventPushDesRecSlotMaybe_250450(s32, s32, s32 *);
s32 strcmp(const char *, const char *);
extern u8 D_0045EB20[];
extern u8 D_00470F50[];
}

static inline s32 iter_begin(It4c *it)
{
    if (it->cur != 0) {
        return -1;
    }
    it->cur = it->head;
    it->done = 0;
    return 0;
}

static inline Ent4c *iter_next(It4c *it, s32 *key)
{
    Node4c *n;
    Node4c *nx;
    Ent4c *d;

    n = it->cur;
    if (n == 0) {
        return 0;
    }
    *key = n->key;
    d = &n->data;
    nx = n->next;
    it->cur = nx;
    if (nx == 0) {
        it->done = 1;
    }
    return d;
}

static inline void iter_end(It4c *it)
{
    it->cur = 0;
    it->done = 0;
}

extern "C" void EventCastLoadPoll_24c230(It4c *it, s32 sys, s32 id)
{
    s32 flag;
    s32 kq;
    s32 *ctx;
    s32 res;
    s32 k4;
    s32 spEC;
    s32 fd;
    s32 k;
    s32 out;
    s32 track;
    Ent4c *e;
    s32 data;

    ctx = GetLoaderMgr_1f59d0();
    flag = -1;
    out = -1;
    if (iter_begin(it) != 0) {
        e = 0;
    } else {
        while ((e = iter_next(it, &k)) != 0) {
            if (id == k) {
                break;
            }
        }
        iter_end(it);
    }
    if (e == 0) {
        return;
    }
    fd = e->m24;
    if (fd < 0) {
        if (e->m4C > 0) {
            f32 n;
            s32 t;
            f32 v;
            t = e->m1C;
            v = ParamTableGetAlpha_1cfb40(sys, t);
            n = e->m4C;
            ParamTableSetAlpha_1cfb10(sys, t, v + (e->m48 - v) / n);
            e->m4C = n - 1.0f;
        }
        return;
    }
    if (e->m20 >= 0) {
        LoaderReleaseById_1cd340(ctx, fd);
        e->m24 = -1;
        LoaderReleaseById_1cd340(ctx, e->m38);
        e->m38 = -1;
        return;
    }
    switch (e->type) {
    case 3:
    case 6:
    case 7: {
        s32 i;
        for (i = 0; i < it->nids; i++) {
            s32 want = it->ids[i];
            Ent4c *q;
            if (id == want) {
                break;
            }
            if (iter_begin(it) != 0) {
                q = 0;
            } else {
                while ((q = iter_next(it, &kq)) != 0) {
                    if (want == kq) {
                        break;
                    }
                }
                iter_end(it);
            }
            if (q->name == 0) {
                continue;
            }
            if (strcmp(e->name, q->name) != 0) {
                continue;
            }
            {
                s32 qt = q->m1C;
                s32 anim = ObjRecGetLiveObject_1c4a90(sys, qt);
                s32 heap;
                Obj4c *o;
                if (anim == 0) {
                    return;
                }
                if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
                    return;
                }
                if ((track = EventCastFindFreeObjSlot_2503e0(sys)) < 0) {
                    return;
                }
                heap = RecStackGetSlot_1c4330(sys, out);
                if (heap == 0) {
                    return;
                }
                e->m1C = track;
                e->m20 = out;
                o = MemStackNew_14e230(0x790, heap);
                if (o != 0) {
                    ModelObjExCtor_1c4920(o);
                    *(u8 **)((u8 *)o + 0x1B0) = D_00470F50;
                }
                if (o == 0) {
                    return;
                }
                o->v5C();
                ModelObjExCopy_1aff40(anim, o, heap);
                GameSceneObjBindMaybe_1cfcd0(sys, track, o, 0);
                switch (e->type) {
                case 3:
                    ObjRecSetFlag2_1c3e80(sys, 1, track);
                    break;
                case 6:
                    ObjRecSetValue_1c3d60(sys, 1, track, 4);
                    ObjRecSetFlags_1c3e00(sys, 1, track, 0x100);
                    ObjRecClearFlag2_1c3e40(sys, 1, track);
                    break;
                case 7:
                    ObjRecSetValue_1c3d60(sys, 1, track, 7);
                    ObjRecSetFlags_1c3e00(sys, 1, track, 0x100);
                    ObjRecClearFlag2_1c3e40(sys, 1, track);
                    break;
                }
                LoaderReleaseById_1cd340(ctx, fd);
                e->m24 = -1;
                e->m44 = qt;
                return;
            }
        }
    }
    }
    switch (LoaderGetStatus_1cd4f0(ctx, fd)) {
    case 0:
        return;
    case -1:
        LoaderReleaseById_1cd340(ctx, e->m24);
        e->m24 = -1;
        LoaderReleaseById_1cd340(ctx, e->m38);
        e->m38 = -1;
        return;
    }
    if (e->m38 >= 0) {
        switch (LoaderGetStatus_1cd4f0(ctx, e->m38)) {
        case 0:
            return;
        case -1:
            LoaderReleaseById_1cd340(ctx, e->m38);
            e->m38 = -1;
            break;
        }
    }
    data = LoaderGetData_1cd490(ctx, fd, &spEC);
    if (data == 0) {
        return;
    }
    res = 0;
    switch (e->type) {
    case 1:
        if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
            return;
        }
        if ((track = EventCastFindFreeObjSlot_2503e0(sys)) < 0) {
            return;
        }
        e->m1C = track;
        e->m20 = out;
        res = EventCastCreateObj_24b8c0(it, sys, out, id, track, data, D_0045EB20, 0);
        ObjRecSetValue_1c3d60(sys, 1, track, 5);
        break;
    case 2:
        if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
            return;
        }
        if ((track = EventCastFindFreeObjSlot_2503e0(sys)) < 0) {
            return;
        }
        e->m1C = track;
        e->m20 = out;
        res = EventCastCreateObj_24b8c0(it, sys, out, id, track, data, D_0045EB20, 0);
        ObjRecSetValue_1c3d60(sys, 1, track, 5);
        break;
    case 3:
        if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
            return;
        }
        if ((track = EventCastFindFreeObjSlot_2503e0(sys)) < 0) {
            return;
        }
        e->m1C = track;
        e->m20 = out;
        res = EventCastCreateObj_24b8c0(it, sys, out, id, track, data, D_0045EB20, 1);
        ObjRecClearFlag2_1c3e40(sys, 1, track);
        flag = 1;
        if (e->m38 >= 0) {
            s32 t = LoaderGetData_1cd490(ctx, e->m38, &spEC);
            Chr4c *c = (Chr4c *)ObjRecGetLiveObject_1c4a90(sys, track);
            s32 h = RecStackGetSlot_1c4330(sys, out);
            if (t != 0 && c != 0 && h != 0) {
                s32 m = GameSceneSoundSlot6LoadBank_1d06d0(sys, t);
                if (m != -1) {
                    c->m4FC = m;
                    c->m518 = (s32)((u8 *)sys + 0xB0A4);
                    c->m4F0 = GameSceneSoundSlot1GetHandle_1d07b0(sys);
                    c->m534 = 0;
                }
            }
        }
        break;
    case 4:
        {
            s32 ky = EventCastFindKeyByName_24bb50(it, e->mC);
            Ent4c *q;
            if (iter_begin(it) != 0) {
                q = 0;
            } else {
                while ((q = iter_next(it, &k4)) != 0) {
                    if (ky == k4) {
                        break;
                    }
                }
                iter_end(it);
            }
            if (q != 0 && q->m44 >= 0) {
                res = 1;
                break;
            }
            if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
                return;
            }
            e->m20 = out;
            res = EventCastObjLoadInfoCfgModels_24b360(it, sys, out, ky, id, data, D_0045EB20);
            e->m1C = EventCastGetObjId_24c160(it, ky);
        }
        break;
    case 5:
        {
            s32 ky;
            if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
                return;
            }
            e->m20 = out;
            ky = EventCastFindKeyByName_24bb50(it, e->mC);
            res = EventCastObjLoadInfoCfg_24b510(it, sys, out, ky, id, data, D_0045EB20);
            e->m1C = EventCastGetObjId_24c160(it, ky);
        }
        break;
    case 6:
        if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
            return;
        }
        if ((track = EventCastFindFreeObjSlot_2503e0(sys)) < 0) {
            return;
        }
        e->m1C = track;
        e->m20 = out;
        res = EventCastCreateObj_24b8c0(it, sys, out, id, track, data, D_0045EB20, 0);
        ObjRecSetValue_1c3d60(sys, 1, track, 4);
        ObjRecSetFlags_1c3e00(sys, 1, track, 0x100);
        ObjRecClearFlag2_1c3e40(sys, 1, track);
        break;
    case 7:
        if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
            return;
        }
        if ((track = EventCastFindFreeObjSlot_2503e0(sys)) < 0) {
            return;
        }
        e->m1C = track;
        e->m20 = out;
        res = EventCastCreateObj_24b8c0(it, sys, out, id, track, data, D_0045EB20, 0);
        ObjRecSetValue_1c3d60(sys, 1, track, 7);
        ObjRecSetFlags_1c3e00(sys, 1, track, 0x100);
        ObjRecClearFlag2_1c3e40(sys, 1, track);
        break;
    case 8:
        {
            s32 t;
            if (EventPushDesRecSlotMaybe_250450(sys, id, &out) == 0) {
                return;
            }
            if ((t = EventCastDataGroupIdAlloc_2503a0(sys)) < 0) {
                return;
            }
            e->m20 = out;
            e->m1C = t;
            res = EventCastRegisterImArchive_24b260(it, sys, out, id, t, data, spEC);
            EventCastSetEnabledMaybe_24aa40(it, id, 0, sys);
        }
        break;
    case 9:
        SoundBankRelease_1bb6e0(4);
        GameSceneSoundSlot6Free_1d0850(sys);
        EventSoundBankHandleSet_24fca0(GameSceneSoundSlot6StartFromData_1d06e0(sys, data), 0);
        res = 1;
        break;
    }
    if (res != 0) {
        if (flag == 1 && it->m32C != 0) {
            ObjRecSetFlag2_1c3e80(sys, 1, track);
        }
    }
    LoaderReleaseById_1cd340(ctx, fd);
    LoaderReleaseById_1cd340(ctx, e->m38);
    e->m24 = -1;
    e->m38 = -1;
}
