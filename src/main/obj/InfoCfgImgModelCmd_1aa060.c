#include "types.h"

typedef struct {
    s32 key;
    s32 idx;
} Slot;

typedef struct Node {
    struct Node *next;
    u8 pad4[0x60];
    s32 x64;
    s32 x68;
} Node;

typedef struct {
    s32 used;
    u8 pad4[0x4C];
} Entry;

typedef struct {
    u8 pad0[0x120];
    s32 x120;
    u8 pad124[0xDC];
    Node *list;
    u8 pad204[0x10];
    s32 count;
    Entry *arr;
    u8 pad21C[0xC];
    Slot slots[4];
} Mgr;

extern void ModelResRelocate_14bfd0(s32 *, s32);
extern s32 ModelBuildFromRes_150f60(Mgr *, Entry *, s32 *, s32, s32);
extern void ModelTagMeshesUnderFrame_1516d0(Mgr *, Entry *, s32, s32);
extern void ModelMeshTagAll_1526d0(Entry *, s32);
extern void ModelPartClear_152810(Entry *);
extern s32 GetDrawCtx_15de80(void);
extern s32 SlotGetInt_15f720(s64 *);
extern s32 VariantGetInt_15f780(s64 *);
extern s32 ArchiveGetFileData_181dd0(s32, s32, s32);
extern s32 D_0049D390[];
extern s32 D_0049D398[];
extern s32 D_0049D3C4[];
extern s32 *D_0049D3C8[];
extern s32 D_0049D3CC[];
extern Mgr *D_0049D418[];
extern s32 D_0049D438[];

static inline Entry *getEntry(Mgr *m, s32 i) {
    if (m->arr == 0) {
        return 0;
    }
    if (i < 0 || i >= m->count) {
        return 0;
    }
    return &m->arr[i];
}

static inline s32 findFree(Mgr *m) {
    s32 i;

    if (m->arr == 0) {
        return 0;
    }
    for (i = 0; i < m->count; i++) {
        if (m->arr[i].used == 0) {
            return i;
        }
    }
    return -1;
}

static inline Slot *getSlot(Mgr *m, s32 key) {
    s32 j;
    Slot *s;

    for (j = 0; j < 4; j++) {
        s = (Slot *)(((j << 3) + (s32)m) + 0x228);
        if (s->idx < 0) {
            s->key = key;
            return s;
        }
    }
    return 0;
}

#pragma opt_propagation off
s32 InfoCfgImgModelCmd_1aa060(s64 *args, s32 argc) {
    Entry *e2;
    Slot *s;
    Mgr *m;
    s32 idx;
    Node *n;
    s32 k20;
    s32 k19;
    Entry *e;
    s32 g;
    s32 key;
    s32 a;
    s32 i;

    s32 sp98[2];

    m = D_0049D418[0];
    k20 = D_0049D398[0];
    k19 = D_0049D390[0];
    if (k20 == 0) {
        return 0;
    }
    g = GetDrawCtx_15de80();
    a = SlotGetInt_15f720(args++);
    key = D_0049D438[0];
    if (argc >= 2) {
        key = VariantGetInt_15f780(args);
    }
    i = 0;
    do {
        s = &m->slots[i];
        if (m->slots[i].key == key) {
            e = getEntry(m, s->idx);
            if (e != 0) {
                ModelPartClear_152810(e);
            }
            s->idx = -1;
            s->key = -1;
        }
        i++;
    } while (i < 4);
    i = ArchiveGetFileData_181dd0(k19, a, 0);
    sp98[0] = 0;
    ModelResRelocate_14bfd0(sp98, i);
    idx = findFree(m);
    e2 = getEntry(m, idx);
    if (e2 == 0) {
        return 0;
    }
    ModelPartClear_152810(e2);
    s = getSlot(m, key);
    if (s == 0) {
        return 0;
    }
    s->idx = idx;
    if (ModelBuildFromRes_150f60(m, e2, sp98, g, k20) == 0) {
        return 0;
    }
    n = m->list;
    ModelMeshTagAll_1526d0(e2, 1);
    while (n != 0) {
        ModelTagMeshesUnderFrame_1516d0(m, e2, n->x68, n->x64);
        n = n->next;
    }
    m->x120 = 0;
    if (D_0049D3C4[0] < D_0049D3CC[0]) {
        i = D_0049D3C4[0];
        D_0049D3C4[0] = i + 1;
        D_0049D3C8[0][i] = key;
    }
    return 1;
}
