#include "types.h"
#pragma always_inline on

typedef struct {
    s32 name;
    u8 pad4[0x2C];
} Entry;

typedef struct {
    s32 unk0;
    s32 count;
    Entry *arr;
} Table;

typedef struct {
    s8 *name;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    f32 unk14;
    f32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    u8 pad28[8];
} Slot;

extern s32 Strcasecmp_1345b8(s32, s8 *);
extern void ModelResRelocate_14bfd0(s32 *, s32);
extern s8 *MemStackAllocQw_14d950(s32, u32);
extern s8 *SlotGetInt_15f720(void);
extern s32 ArchiveGetFileData_181dd0(s32, s8 *, s32 *);
extern void FarClipRecGetPresetFadeRates_186e70(s32, s32 *, s32 *);
extern s8 *strcpy(s8 *, s8 *);
extern u32 strlen(s8 *);

extern s32 D_00481310;
extern s32 D_00481318;
extern s32 D_0048131C;
extern Table *D_00481320;
extern Slot *D_00481324;
extern Slot *D_00481328;
extern s32 D_0048132C;
extern s32 D_00481330;
extern s32 D_00481338;
extern s32 D_00481350;
extern s32 D_00481354;

static inline s32 findEntry(Table *t, s8 *name)
{
    s32 i;
    if (name == NULL || *name == 0) {
        return -1;
    }
    for (i = 0; i < t->count; i++) {
        if (t->arr[i].name != 0 && Strcasecmp_1345b8(t->arr[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline Entry *getEntry(Table *t, s32 i)
{
    if (i < 0 || i >= t->count) {
        return NULL;
    }
    return &t->arr[i];
}

static inline Entry *lookup(Table *t, s8 *name)
{
    s32 i = findEntry(t, name);
    if (i < 0) {
        return NULL;
    }
    return getEntry(t, i);
}

s32 MapModelCfgMds_195f20(void)
{
    //DECLS
    s8 *name;
    Table *t;
    Slot *slot;
    s32 n;
    u32 len;
    u32 words;
    s8 *buf;
    s32 r;
    s32 sp4C;
    //ENDDECLS

    if (D_00481318 >= D_0048131C) {
        D_00481328 = NULL;
        return 0;
    }
    name = SlotGetInt_15f720();
    if (name != NULL) {
        t = D_00481320;
        if (lookup(t, name) != NULL) {
            D_00481328 = NULL;
            return 0;
        }
    }
    n = D_00481318;
    slot = &D_00481324[n];
    D_00481318 = n + 1;
    D_00481328 = slot;
    slot->name = NULL;
    slot->unk4 = 0;
    slot->unk8 = 0;
    slot->unk18 = -1.0f;
    slot->unk14 = -1.0f;
    slot->unk1C = 0;
    slot->unkC = 0;
    slot->unk10 = 0;
    FarClipRecGetPresetFadeRates_186e70(0, &slot->unk20, &slot->unk24);
    if (name == NULL) {
        D_00481328->name = NULL;
    } else {
        len = strlen(name) + 1;
        if (len & 0xF) {
            words = (len >> 4) + 1;
        } else {
            words = len >> 4;
        }
        buf = MemStackAllocQw_14d950(D_0048132C, words);
        strcpy(buf, name);
        D_00481328->name = buf;
    }
    D_00481310 = 0;
    r = ArchiveGetFileData_181dd0(D_00481330, D_00481328->name, &sp4C);
    if (r == 0) {
        return 0;
    }
    ModelResRelocate_14bfd0(&D_00481310, r);
    D_00481350 = 0;
    D_00481338 = 0;
    D_00481354 = 0;
    return 1;
}
