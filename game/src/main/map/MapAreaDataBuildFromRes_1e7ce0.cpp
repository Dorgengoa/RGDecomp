/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_propagation off

typedef struct Res {
    s16 x0;
    s16 flag;
    s32 ptr;
    s32 size;
} Res;

typedef struct Slot {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Slot;

typedef struct Table {
    s32 count;
    s32 pad[3];
    Slot slot[1];
} Table;

typedef struct Obj {
    u8 pad0[0xC];
    Res r[3];
    u8 x30[0x70];
    s32 xA0;
    u8 padA4[0x240 - 0xA4];
    s32 x240;
    u8 pad244[0x2B0 - 0x244];
    Table *x2B0;
    u8 pad2B4[0x16C0 - 0x2B4];
    s32 x16C0;
    s32 x16C4;
    s16 x16C8;
    s16 pad16CA;
    s32 x16CC;
    s32 x16D0;
    s32 x16D4;
    s32 x16D8;
    u8 pad16DC[8];
    s32 x16E4[4];
    s32 x16F4[4];
} Obj;

extern "C" {
s32 MemStackPeekQw_14d9d0(s32, s32);
void TexGroupAllocVramDefault_158ab0(s32, s32);
s32 NameTableRegisterImArchive_1594d0(s32, s32, s32, s32, void *);
s32 GetDrawCtxNameTable_15de40(void);
void FuncAnimeArrayBuild_187250(void *, s32);
void MapAreaModelBuildBoundsMaybe_188ff0(void *, s32);
void MapAreaModelBuildStubRelated_1899b0(void);
void MapAreaModelCfgParse_189e30(void *, s32, s32, s32);
void MapCfgParse_18a250(void *, s32, s32, s32, s32);
void MapSceneCfgParse_1923e0(void *, s32, s32, s32, s32);
s32 MapSceneCfgGetPcpName_193720(void *, s32);
s32 CountedArrayGet_193760(void *, s32);
void MapModelCfgLoad_195550(Slot *, s32, s32, s32, s32);
s32 SceneTableFindNamedData_196290(Table *, s32);
s32 SceneTableAddNamedData_1963e0(Table *, s32, void *, s32);
s32 SceneTableFindModelCfg_1967f0(Table *, s32);
s32 ArchiveGetFileByPath_1c2800(s32, s32, s32);
void ObjRecSetFlag2_1c3e80(u8 *, s32, s32);
void ObjRecSetRes_1c52a0(u8 *, s32, s32, s32, s32, s32);
s16 ObjRecTableBindSlot_1c53a0(u8 *, s32, void *, s32);
void LoaderReleaseHandle_1ccb70(Res *);
void MapAreaDataDupResLogStubMaybe_1e9920(void);
u8 *GetCurrentScene_1f5be0(void);
extern u8 D_0045B4B8[];
extern u8 D_0045B4C0[];
}

static inline bool isNull(s32 x) { return x == 0; }
static inline bool isFree(Slot *s) { return (s->c != 0) ^ 1 || (s->a != 0) ^ 1; }
static inline bool isFree2(Slot *s) { return isNull(s->c) || isNull(s->a); }

extern "C" s32 MapAreaDataBuildFromRes_1e7ce0(Obj *o)
{
    u8 buf[0x100] __attribute__((aligned(16)));
    u8 *g;
    Table *tbl;
    s32 h;
    s32 pos;
    s32 n;
    s32 i;
    s32 id;
    s32 obj;

    if (o->r[0].flag == 0) {
        return 0;
    }
    if (o->r[0].ptr == 0 || o->r[0].size <= 0) {
        return -1;
    }
    if (o->r[1].flag == 0) {
        return 0;
    }
    if (o->r[1].ptr == 0 || o->r[1].size <= 0) {
        return -1;
    }
    if (o->r[2].flag == 0) {
        return 0;
    }
    g = GetCurrentScene_1f5be0();
    o->x16C8 = ObjRecTableBindSlot_1c53a0(g, -1, o->x30, o->x16D8);
    if (o->x16C8 < 0) {
        return -1;
    }
    o->x2B0 = (Table *)(g + 0x4020);
    MapSceneCfgParse_1923e0(&o->xA0, o->r[1].ptr, o->r[1].size, o->x16D4, 0);
    tbl = (Table *)(g + 0x4020);
    o->x16C4 = o->x16C0 = o->x16C8 * 16 + 16;
    h = GetDrawCtxNameTable_15de40();
    pos = o->x16C0;
    n = 0;
    for (i = 0; i < o->xA0; i++) {
        id = CountedArrayGet_193760(&o->xA0, i);
        if (id == 0) {
            continue;
        }
        obj = ArchiveGetFileByPath_1c2800(o->x16CC, id, 0);
        if (SceneTableFindNamedData_196290(tbl, id) != 0) {
            MapAreaDataDupResLogStubMaybe_1e9920();
        } else if (obj != 0) {
            s32 old = pos;
            pos += NameTableRegisterImArchive_1594d0(h, obj, pos, o->x16D4, buf);
            pos++;
            TexGroupAllocVramDefault_158ab0(h, old);
            if (SceneTableAddNamedData_1963e0(tbl, id, buf, o->x16D4) != 0) {
                o->x16E4[n++] = id;
            }
        }
    }
    o->x16E4[n] = 0;
    o->x16C4 = pos - o->x16C0;
    {
        n = 0;
        h = o->r[0].ptr;
        for (id = 0;; id++) {
            pos = MapSceneCfgGetPcpName_193720(&o->xA0, id);
            if (pos == 0) {
                break;
            }
            i = ArchiveGetFileByPath_1c2800(h, pos, 0);
            if (i == 0) {
                continue;
            }
            if (SceneTableFindModelCfg_1967f0(tbl, pos) != 0) {
                MapAreaDataDupResLogStubMaybe_1e9920();
            } else {
                Slot *found = 0;
                s32 k;
                for (k = 0; k < tbl->count; k++) {
                    bool ok = true;
                    if (!isFree(&tbl->slot[k]) && tbl->slot[k].b != 0) {
                        ok = false;
                    }
                    if ((ok & 0xFF) != 0) {
                        found = &tbl->slot[k];
                        break;
                    }
                }
                if (found != 0) {
                    MapModelCfgLoad_195550(found, pos, i, o->x16D4, o->x240);
                    o->x16F4[n++] = pos;
                }
            }
        }
        o->x16F4[n] = 0;
    }
    if (MemStackPeekQw_14d9d0(o->x16D4, 1) == 0) {
        return -1;
    }
    ObjRecSetRes_1c52a0(g, o->x16C8, o->x16D4, 1, o->x16C0, o->x16C4);
    ObjRecSetFlag2_1c3e80(g, 2, o->x16C8);
    MapAreaModelBuildStubRelated_1899b0();
    MapCfgParse_18a250(o->x30, o->r[1].ptr, o->r[1].size, o->x16D4, 0);
    MapAreaModelBuildBoundsMaybe_188ff0(o->x30, o->x16D4);
    FuncAnimeArrayBuild_187250(o->x30, o->x16D4);
    LoaderReleaseHandle_1ccb70(&o->r[0]);
    LoaderReleaseHandle_1ccb70(&o->r[1]);
    if (o->r[2].ptr == 0 || o->r[2].size <= 0) {
        return 2;
    }
    MapAreaModelCfgParse_189e30(o->x30, o->r[2].ptr, o->r[2].size, o->x16D4);
    LoaderReleaseHandle_1ccb70(&o->r[2]);
    return 2;
}
