#include "types.h"


typedef struct { f32 x, y, z, w; } V4;
typedef struct {
    u8 pad0[0x10];
    V4 pos;
} Ent;
typedef struct {
    s32 idx;
    u8 pad4[0x14];
    s32 f18;
    s32 f1C;
} Lnk;
typedef struct {
    u8 pad0[0x60];
    u32 flags;
    u8 pad64[0xC];
    s32 f70;
} Elem;
typedef struct {
    u8 pad0[0x9C];
    s32 n;
} Info;
typedef struct { u8 b[12]; } Slot;
typedef struct St {
    Slot slots[4];
    u8 pad30[0x1694 - 0x30];
    u8 it[0x16B0 - 0x1694];
    void *arr;
    Ent *ents;
    s16 cnt;
    s16 nent;
    u8 bgn;
    u8 pad16BD[0x16C4 - 0x16BD];
    s32 lvl;
    s16 f16C8;
    s16 state;
    u8 pad16CC[0x16D4 - 0x16CC];
    void *heap;
    void *f16D8;
    Lnk *lnks;
    s32 nlnk;
} St;

s32 MapAreaDataLoadCopyIpk_1e8150(St *);
s32 MapAreaDataLoadStepStub13_1e8140(St *);
s32 MapAreaDataLoadStepStub14_1e8130(St *);
s32 MapAreaDataLoadStepStub15_1e8120(St *);
s32 MapAreaDataBuildFromRes_1e7ce0(St *);
Info *MapAreaDataGetSceneCfg_1e8bf0(St *);
void MemStackAllocAligned64_14da10(void *, s32);
void *MemStackNew_14e1b0(s32, void *);
void MapLightSetCtor_1923a0();
void *ConstructNewArray_100710(void *, void (*)(), s32, s32, s32);
void FuncDataTableIterBegin_1908e0(void *, s32);
Elem *FuncDataTableIterNext_1908b0(void *);
void NodeGetRotation_1865e0(Elem *, Ent *);
void NodeGetTranslation_186650(Elem *, V4 *);
void MapLinkSetPos_1e9220(Lnk *, V4 *);
s32 MapLinkGetEntIndex_1e9300(Lnk *);
f32 VecDistSqXZ_1cb390(V4 *, V4 *);
f32 Floorf_128e30(f32);
void *GetCurrentScene_1f5be0(void);
void ObjRecSetFlags_1c3e00(void *, s32, s32, s32);
void ObjRecSetFlag2_1c3e80(void *, s32, s32);
void AlignUp16_1cacd0(s32);
void Nop_1e99c0(void);
void MapAreaLoadDebugStubRelated_1e99b0(void);
void LoaderReleaseHandle_1ccb70(Slot *);
extern f32 D_0045B080[];
extern f32 D_0047DB50;

void MapAreaDataLoadStep_1e83f0(St *s) {
    s32 r;
    Info *info;
    s32 n;
    void *it;
    Elem *e;
    s32 j;
    f32 ofs;
    f32 scale;
    s32 k;
    Elem *e2;
    s32 i;
    s32 m;
    void *w;


    if (s->state == 0) {
        return;
    }
    if (s->heap == 0 || s->f16D8 == 0) {
        s->state = 1;
    }
    switch (s->state) {
    case 11:
        r = MapAreaDataLoadCopyIpk_1e8150(s);
        if (r != 0) {
            if (r == -1) {
                s->state = 1;
            } else {
                s->state = 13;
                if (r == 1) {
                    MapAreaDataLoadStep_1e83f0(s);
                }
            }
        }
        break;
    case 13:
        r = MapAreaDataLoadStepStub13_1e8140(s);
        if (r != 0) {
            if (r == -1) {
                s->state = 1;
            } else {
                s->state = 14;
                if (r == 1) {
                    MapAreaDataLoadStep_1e83f0(s);
                }
            }
        }
        break;
    case 14:
        r = MapAreaDataLoadStepStub14_1e8130(s);
        if (r != 0) {
            if (r == -1) {
                s->state = 1;
            } else {
                s->state = 15;
                if (r == 1) {
                    MapAreaDataLoadStep_1e83f0(s);
                }
            }
        }
        break;
    case 15:
        r = MapAreaDataLoadStepStub15_1e8120(s);
        if (r != 0) {
            if (r == -1) {
                s->state = 1;
            } else {
                s->state = 16;
                if (r == 1) {
                    MapAreaDataLoadStep_1e83f0(s);
                }
            }
        }
        break;
    case 16:
        r = MapAreaDataBuildFromRes_1e7ce0(s);
        if (r != 0) {
            if (r == -1) {
                s->state = 1;
            } else {
                s->state = 2;
                return;
            }
        }
        break;
    case 2:
        break;
    default:
        s->state = 0;
        break;
    }
    switch (s->state) {
    case 2:
        break;
    case 1:
        goto done;
    default:
        return;
    }
        info = MapAreaDataGetSceneCfg_1e8bf0(s);
        if (info->n > 0) {
            MemStackAllocAligned64_14da10(s->heap, 1);
            n = info->n;
            s->arr = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x1D0 + 0x10, s->heap), MapLightSetCtor_1923a0, 0, 0x1D0, n);
            if (s->arr == 0) {
                s->state = 1;
                MapAreaDataLoadStep_1e83f0(s);
                return;
            }
            s->cnt = info->n;
        }
        it = s->it;
        s->nent = 0;
        s->nlnk = 0;
        FuncDataTableIterBegin_1908e0(it, 6);
        while ((e = FuncDataTableIterNext_1908b0(it)) != 0) {
            if (e->flags & 0x20) {
                s->nlnk++;
            }
            s->nent++;
        }
        s->ents = MemStackNew_14e1b0(s->nent << 5, s->heap);
        s->lnks = MemStackNew_14e1b0(s->nlnk << 5, s->heap);
        if ((s->nent > 0 && s->ents == 0) || (s->nlnk > 0 && s->lnks == 0)) {
            s->state = 1;
            MapAreaDataLoadStep_1e83f0(s);
            return;
        }
        if (s->nent > 0) {
            FuncDataTableIterBegin_1908e0(it, 6);
            for (j = 0, i = 0; i < s->nent; i++) {
                e = FuncDataTableIterNext_1908b0(it);
                NodeGetRotation_1865e0(e, &s->ents[i]);
                NodeGetTranslation_186650(e, &s->ents[i].pos);
                if (e->flags & 0x20) {
                    s->lnks[j].idx = i;
                    MapLinkSetPos_1e9220(&s->lnks[j], &s->ents[i].pos);
                    j++;
                }
            }
            FuncDataTableIterBegin_1908e0(it, 6);
{ f32 a = *(volatile f32 *)&D_0045B080[0]; scale = D_0047DB50 * a; }
 k = 0;
 ofs = 0.25f * scale;
 for (; k < s->nent; k++) {
                e2 = FuncDataTableIterNext_1908b0(it);
                if (!(e2->flags & 0x40)) {
                    continue;
                }
                for (m = 0; m < s->nlnk; m++) {
                    if (VecDistSqXZ_1cb390(&s->ents[k].pos, &s->ents[MapLinkGetEntIndex_1e9300(&s->lnks[(u32)m])].pos) <= 1.0f) {
                        s->lnks[m].f18 = Floorf_128e30((ofs + (s->ents[k].pos.y - s->ents[MapLinkGetEntIndex_1e9300(&s->lnks[m])].pos.y)) / scale);
                        s->lnks[m].f1C = e2->f70;
                    }
                }
            }
        }
        w = GetCurrentScene_1f5be0();
        ObjRecSetFlags_1c3e00(w, 2, s->f16C8, 1);
        ObjRecSetFlag2_1c3e80(w, 2, s->f16C8);
        AlignUp16_1cacd0(0x58);
        s->bgn = 1;
        if (s->lvl > 8) {
            Nop_1e99c0();
            MapAreaLoadDebugStubRelated_1e99b0();
        }
        Nop_1e99c0();
        Nop_1e99c0();
        if (s->lvl > 8) {
            MapAreaLoadDebugStubRelated_1e99b0();
            Nop_1e99c0();
        }
done:
    for (i = 0; i < 4; i++) {
        LoaderReleaseHandle_1ccb70(&s->slots[i]);
    }
    s->state = 0;

}
