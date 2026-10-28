/* rgp:protos */
#define RGP_SELF_MinimapLoad_32a240 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct {
    u8 b[0x830];
} Strm32a;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec32a;

typedef struct {
    u8 pad0[0x80];
    s32 x80;
    s32 x84[16];
    s32 xC4;
    s32 xC8;
    u8 padCC[0x104 - 0xCC];
    s16 x104;
    s16 x106;
    u8 pad108[4];
    s16 x10C;
    u8 pad10E[0x11A - 0x10E];
    s8 x11A;
    u8 pad11B[0x120 - 0x11B];
    u8 m120[0xC];
    u8 m12C[0x34];
    s32 x160;
    f32 x164;
    s32 x168;
    s32 x16C;
} Obj32a;

/*rgp*/
/*rgp*/
/*rgp*/
void *memcpy(void *, const void *, u32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 strcmp(const char *, const char *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00452710[];
extern u8 D_004527D0[];
extern u8 D_00462428[];
extern u8 D_00462438[];
extern u8 D_00462448[];
extern f32 D_0047F350;
extern f32 D_0047F354;
extern f32 D_0047F358;
extern f32 D_0047F35C;

s32 MinimapLoad_32a240(Obj32a *self, void *data, s32 size, s32 id, s32 p4, s32 p5, s32 p6, s32 p7, s32 arg8)
{
    Strm32a s1 __attribute__((aligned(16)));
    Strm32a s2 __attribute__((aligned(16)));
    Vec32a v __attribute__((aligned(16)));
    s32 buf;
    s32 tex;
    s32 h;
    s32 a;
    void *lst;
    s32 n;
    s32 i;
    s32 it;
    char *name;
    s32 e;

    MinimapInit_32a660((void *)self);
    if (data == 0 || size <= 0 || id < 0 || p4 == 0 || p5 <= 0) {
        return 0;
    }
    buf = MemStackAllocQw_14d950(arg8, AlignUp16_1cacd0(size) >> 4);
    memcpy((void *)buf, data, size);
    self->x10C = id;
    tex = GetDrawCtxNameTable_15de40();
    NameTableRegisterImArchive_1594d0(tex, buf, self->x10C, arg8, 0);
    h = GetDrawCtx_15de80();
    a = DrawEnvGetWidth_1451e0(h);
    NameTableAddEntry_159b70(tex, self->x10C, D_00462428, 0, a, DrawEnvGetHeight_1451d0(h), 0x20, 0, 0, (int)(0));
    lst = self->m12C;
    SetEntryTableGlobal_32c2d0(lst);
    EntryListReset_3237f0(lst);
    EntryListSetHeap_3237e0(lst, arg8);
    EntryListSelectByIndex_323540(lst, 0);
    CfgVmReset_42fc10(&s1);
    CfgVmRegisterCmds_42fb00(&s1, D_00452710);
    CfgVmLoad_42fac0(&s1, p4, p5);
    CfgVmRun_42fa20(&s1);
    n = ((short)EntryListGetCount_323680(lst));
    for (i = 0; i < n; i++) {
        it = EntryListSelectByIndex_323540(lst, i);
        if (it == 0) {
            continue;
        }
        if (EntryGetGroupId_3238d0(it) != -1) {
            continue;
        }
        EntrySetGroupId_3238e0(it, self->x104);
        name = (char *)it + 0x54;
        it = EntryListSelectByIndex_323540(lst, 0);
        do {
            if (EntryGetGroupId_3238d0(it) == -1 && strcmp(name, (char *)it + 0x54) == 0) {
                EntrySetGroupId_3238e0(it, self->x104);
            }
            it = EntryListSelectNext_323500(lst);
        } while (it != 0);
        self->x104++;
    }
    EntryListSelectByIndex_323540(lst, 0);
    SetMinimapSubGlobal_32c2b0(self->m120);
    MinimapSubReset_32af90(self->m120);
    MinimapSubSetHeap_32af80(self->m120, arg8);
    if (p6 != 0 && p7 != 0) {
        CfgVmReset_42fc10(&s2);
        CfgVmRegisterCmds_42fb00(&s2, D_004527D0);
        CfgVmLoad_42fac0(&s2, p6, p7);
        CfgVmRun_42fa20(&s2);
    }
    self->x11A = 1;
    self->x106 = -1;
    self->x106 = 0;
    v.x = D_0047F350;
    v.y = D_0047F354;
    v.z = D_0047F358;
    v.w = D_0047F35C;
    {
        Vec32a *pv = &v;
        MinimapSetTargetPosMaybe_324bb0(self, pv);
    }
    self->x11A |= 2;
    if (tex != 0) {
        self->x80 = ((s32)NameTableFindByName_159fb0(tex, D_00462438, 0x32B));
        self->xC4 = ((s32)NameTableFindByName_159fb0(tex, D_00462448, ((short)MinimapGetTexGroup_32a1e0(self))));
        self->xC8 = ((s32)NameTableFindByName_159fb0(tex, D_00462428, ((short)MinimapGetTexGroup_32a1e0(self))));
        for (i = 0; i < ((unsigned char)EntryListGetChildCount_323790(lst)); i++) {
            e = ((s32)EntryListGetChild_3233c0(lst, i));
            if (e == 0) {
                continue;
            }
            e = (s32)EntryChildGetName_323cf0(e);
            self->x84[i] = ((s32)NameTableFindByName_159fb0(tex, (void *)e, ((short)MinimapGetTexGroup_32a1e0(self))));
        }
    }
    self->x106 = 0;
    MinimapRequestEntry_32ab90(self, EntryListSelectByIndex_323540(lst, 0));
    self->x164 = 1.0f;
    self->x160 = 0;
    self->x16C = 0;
        return 1;
}
