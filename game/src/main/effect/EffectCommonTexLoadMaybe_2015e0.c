/* rgp:protos */
#define RGP_SELF_EffectCommonTexLoadMaybe_2015e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    char name[0x20];
    char name2[0x28];
    u16 unk48;
    u16 unk4A;
    s32 unk4C;
} Ent002015e0;

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
extern void *memcpy(void *, const void *, u32);
extern void strcpy(void *, void *);

extern u8 D_0045C0D0[0x400];
extern u8 D_0045C0F0[0x400];
extern u8 D_0045C108[0x400];
extern u8 D_0045C110[0x400];
extern u8 D_0045C120[0x400];

void EffectCommonTexLoadMaybe_2015e0(void) {
    s32 sp6C;
    s32 heap;
    s32 arc;
    void *buf;
    s32 id;
    void *p;
    Ent002015e0 *e;

    heap = ((s32)GetSystemMemStack_202600());
    arc = ((s32)GetReadBuffHeap_2025e0());
    buf = MemStackHeapAlloc_14db10(arc, 2, 0, 0x40);
    if (buf == NULL) {
        return;
    }
    MemStackAlign64_14d8e0(arc);
    id = GetDrawCtxNameTable_15de40();
    if (ResidentFileReadLocalizedMaybe_1c2860(D_0045C0D0, buf, &sp6C) != 0) {
        p = MemStackAllocQw_14d950(heap, sp6C / 16 + 1);
        memcpy(p, buf, sp6C);
        NameTableRegisterImArchive_1594d0(id, p, 0x31D, heap, 0);
        MemStackAlign64_14d8e0(heap);
    }
    if (ResidentFileReadLocalizedMaybe_1c2860(D_0045C0F0, buf, &sp6C) != 0) {
        p = MemStackAllocQw_14d950(heap, sp6C / 16 + 1);
        memcpy(p, buf, sp6C);
        NameTableRegisterImArchive_1594d0(id, p, 0x30D, heap, 0);
        MemStackAlign64_14d8e0(heap);
    }
    e = ((Ent002015e0 *)TexPairGet_18fa20(0));
    strcpy(e->name, D_0045C108);
    strcpy(e->name2, D_0045C110);
    e->unk48 = 0x100;
    e->unk4A = 0x100;
    e->unk4C = 0xA;
    TexPairResolve_18fb10(e);
    e = ((Ent002015e0 *)TexPairGet_18fa20(1));
    strcpy(e->name, D_0045C120);
    strcpy(e->name2, D_0045C110);
    e->unk48 = 0x200;
    e->unk4A = 0x100;
    e->unk4C = 0x20;
    TexPairResolve_18fb10(e);
    MemStackReturnToOwnerMaybe_14dad0(arc);
    MemStackHeapFree_14dcb0(arc, buf);
    
}
