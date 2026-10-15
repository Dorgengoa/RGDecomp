#include "types.h"

typedef struct {
    u8 pad0[2];
    s16 unk2;
    s32 unk4;
} Obj001D8A10;

typedef struct {
    s32 unk0;
    u8 pad4[0xA4];
    u8 unkA8[4];
} Self001D8A10;

void Sprintf_1343b8(char *, u8 *, s32);
s32 ArchiveGetFileByPath_1c2800(s32, char *, s32 *);
s32 ObjRecTableFindFree_1c5320(s32);
s32 MapAreaGetFileStem_1dce70(Self001D8A10 *);
Obj001D8A10 *MapAreaLoadHandleAt_1dd120(void *, s32);
s32 MapDataGetName_1e7bf0(Self001D8A10 *);
s32 GetCurrentScene_1f5be0();
s32 GetMinimapMgr_201a70();
void MinimapMgrAdd_322170(s32, s32, s32, s32, s32, s32, s32, s32, s64, s64);
void LoadHandlePollThunk_1ccb00(void *);
extern u8 D_0045B2E0[0x10];
extern u8 D_0045B2F0[0x20];
extern u8 D_0045B310[0x20];

s32 MapAreaLoadMinimap_1d8a10(Self001D8A10 *self)
{
    s32 sp14C;
    s32 sp148;
    s32 sp144;
    char b100[0x40];
    char bC0[0x40];
    char b80[0x40];
    s32 a;
    s32 b;
    s32 c;
    s32 r;
    s32 h;
    Obj001D8A10 *p;

    LoadHandlePollThunk_1ccb00(self->unkA8);
    r = ObjRecTableFindFree_1c5320(GetCurrentScene_1f5be0());
    if (r < 0) {
        return -1;
    }
    p = MapAreaLoadHandleAt_1dd120(self->unkA8, 0);
    if (p == NULL) {
        return -1;
    }
    if (p->unk2 == 0) {
        return 0;
    }
    if (p->unk2 == -1) {
        return 1;
    }
    Sprintf_1343b8(b100, D_0045B2E0, MapAreaGetFileStem_1dce70(self));
    Sprintf_1343b8(bC0, D_0045B2F0, MapAreaGetFileStem_1dce70(self));
    Sprintf_1343b8(b80, D_0045B310, MapAreaGetFileStem_1dce70(self));
    a = ArchiveGetFileByPath_1c2800(p->unk4, b100, &sp14C);
    b = ArchiveGetFileByPath_1c2800(p->unk4, bC0, &sp148);
    c = ArchiveGetFileByPath_1c2800(p->unk4, b80, &sp144);
    h = GetMinimapMgr_201a70();
    MinimapMgrAdd_322170(h, MapDataGetName_1e7bf0(self), a, sp14C, r + 0x164, b, sp148, c, sp144, self->unk0);
    return 2;
}
