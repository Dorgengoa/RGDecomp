/* rgp:protos */
#line 1
/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/MapAreaRelease_1d9ee0.s and build/b_drafts/MapAreaRelease_1d9ee0.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"

extern "C" {
s32 MapDataGetState_1e7a00(u8 *);
u8 *MapAreaGetBlocks_1dce30(u8 *);
s32 MapAreaGetBlockCount_1dce20(u8 *);
u8 *MapAreaGetShares_1dce60(u8 *);
s32 MapAreaGetShareCount_1dce50(u8 *);
void MapAreaReleaseBlockIfOwned_1d9d20(u8 *, u8 *, s32);
void MapAreaUnloadShareIfUnused_1d9db0(u8 *, u8 *, s32);
bool MapDataIsLoaded_1e79d0(u8 *);
void LoadHandleRelease_1dd160(u8 *);
void MapAreaEffectsRelease_1e90c0(void *);
void *MapDataGetName_1e7bf0(u8 *);
void *GetMinimapMgr_201a70(void);
void MinimapMgrRelease_3220c0(void *, void *);
void MapAreaDataRelease_1e8ef0(void *);
void *MapDataGetId_1e7bd0(u8 *);
void EventObjMgrRemoveByAreaFwd_2fd9a0(void *);
void MemStackHeapFree_14dcb0(void *, void *);
void GetDrawCtxNameTable_15de40(void);
void MapAreaTreasureBoxSlotRelease_1de8b0(u8 *);
void MapAreaClearLoadState_1dcf30(u8 *);
}

struct Self {
    void *m0;
    void *m4;
    void *m8;
    u8 padC[0x16];
    u8 m22;
    u8 pad23[0x9];
    s32 m2C;
    u8 pad30[0x54];
    void *m84;
    u8 pad88[0x20];
    u8 mA8[0xC];
    u8 mB4[4][0xC];
    u8 padE4[4];
    s32 mE8;
    s32 mEC;
    s32 mF0;
    s32 mF4;
};

extern "C" s32 MapAreaRelease_1d9ee0(Self *self, s32 flag)
{
    bool any;
    u8 *p;
    s32 n;
    s32 i;
    void *g;

    if (((signed char)MapDataGetState_1e7a00((u8 *)self)) == -1) {
        return 0;
    }
    any = false;
    p = MapAreaGetBlocks_1dce30((u8 *)self);
    if (p != 0) {
        n = MapAreaGetBlockCount_1dce20((u8 *)self);
        for (i = 0; i < n; i++, p += 0xCC) {
            MapAreaReleaseBlockIfOwned_1d9d20((u8 *)self, p, flag);
            any |= MapDataIsLoaded_1e79d0(p);
        }
    }
    p = MapAreaGetShares_1dce60((u8 *)self);
    if (p != 0) {
        n = MapAreaGetShareCount_1dce50((u8 *)self);
        for (i = 0; i < n; i++, p += 0x58) {
            MapAreaUnloadShareIfUnused_1d9db0((u8 *)self, p, flag);
            any |= MapDataIsLoaded_1e79d0(p);
        }
    }
    if (flag == 0) {
        if (any || (self->m2C & 2)) {
            return 0;
        }
    }
    LoadHandleRelease_1dd160(self->mA8);
    if (self->m84 != 0) {
        MapAreaEffectsRelease_1e90c0(self->m84);
    }
    if (MapDataGetName_1e7bf0((u8 *)self) != 0) {
        g = GetMinimapMgr_201a70();
        MinimapMgrRelease_3220c0(g, MapDataGetName_1e7bf0((u8 *)self));
    }
    if (self->m8 != 0) {
        MapAreaDataRelease_1e8ef0(self->m8);
        self->m8 = 0;
    }
    EventObjMgrRemoveByAreaFwd_2fd9a0(((void *)(long)(short)MapDataGetId_1e7bd0((u8 *)self)));
    if (self->m0 != 0 && self->m4 != 0) {
        MemStackHeapFree_14dcb0(self->m4, self->m0);
    }
    self->m0 = 0;
    self->m4 = 0;
    self->m22 = 0;
    self->mE8 = 0;
    self->mEC = 0;
    self->mF0 = 0;
    self->mF4 = 0;
    GetDrawCtxNameTable_15de40();
    for (i = 0; i < 4; i++) {
        MapAreaTreasureBoxSlotRelease_1de8b0(self->mB4[i]);
    }
    MapAreaClearLoadState_1dcf30((u8 *)self);
    return 1;
}
