#include "types.h"

struct Res {
    s16 type;
    s32 val;
    s32 z;
    s32 w;
    Res() {}
    Res(const Res &o) : type(o.type), val(o.val), z(o.z), w(o.w) {}
};

typedef struct Sub {
    s16 h0;
    s16 h2;
    s32 w4;
    s16 h8;
    u8 padA[4];
    s16 hE;
    s16 h10;
    char name12[0x20];
    char name32[0x20];
} Sub;

typedef struct Ent {
    u8 pad0[0xC];
    Sub sub;
    u8 pad[0xE0 - 0xC - sizeof(Sub)];
} Ent;

typedef struct Mgr {
    Ent ents[48];
    s32 w2A00;
} Mgr;

extern "C" {
void Sprintf_1343b8(char *, const char *, void *, void *);
void LoaderReleaseById_1cd340(s32, s16);
s16 LoaderRequestFile_1cd870(s32, char *, s32);
void LoaderQueueAppendSeparator_1cd670(s32);
s32 GetLoaderMgr_1f59d0(void);
s32 EffectFindByName_2dfe10(Mgr *, s32, s16 *);
void EffectFindFreeSlot_2dfdd0(Mgr *, s16 *);
void StrReplaceExt_2dfd30(char *, s32, void *);
void EffectEntrySetHeaps_2dc540(Ent *, s32, s32, s32);
void EffectEntryReset_2dc550(Ent *);
void EffectEntrySetName_2d9550(Ent *, s32);
char *strcpy(char *, const char *);
s32 strlen(const char *);
extern char D_00461770[];
extern char D_00461778[];
extern char D_00461780[];
extern char D_00461788[];
extern char D_00461768[];
}

extern "C" Res EffectRequestLoadImg_2df3a0(Mgr *m, s32 a2, s32 a3, s32 a4, s32 a5, void *a6, s32 a7) {
    Res r2;
    Res r;
    char buf120[0x40];
    char bufE0[0x40];
    char bufA0[0x40];
    s16 idx;
    s16 slot;
    Sub *sub;
    s32 g;
    s32 n;
    char *p;
    bool found;
    s32 i;
    s32 v;

    idx = 0;
    if (EffectFindByName_2dfe10(m, a4, &idx) != 0) {
        r2.type = 3;
        r2.val = idx;
        r2.z = 0;
        return r2;
    }
    slot = -1;
    EffectFindFreeSlot_2dfdd0(m, &slot);
    if (slot < 0) {
        r.type = 3;
        r.val = -1;
        r.z = 0;
        return r;
    }
    StrReplaceExt_2dfd30(buf120, a5, D_00461768);
    Sprintf_1343b8(bufE0, D_00461778, a6, D_00461770);
    sub = &m->ents[slot].sub;
    EffectEntrySetHeaps_2dc540(&m->ents[slot], a2, m->w2A00, slot);
    EffectEntrySetName_2d9550(&m->ents[slot], a4);
    sub->h8 = slot + 0x2DB;
    g = GetLoaderMgr_1f59d0();
    if (g == 0) {
        r.type = 3;
        r.val = -1;
        r.z = 0;
        return r;
    }
    sub->h0 = 1;
    sub->h2 = slot;
    v = slot;
    sub->w4 = a7;
    n = strlen(buf120);
    p = buf120;
    found = false;
    for (i = 0; i < n; i++) {
        if (*p == '/') {
            found = true;
            break;
        }
        p++;
    }
    if (found) {
        strcpy(bufA0, buf120);
    } else {
        Sprintf_1343b8(bufA0, D_00461778, D_00461780, buf120);
    }
    sub->hE = LoaderRequestFile_1cd870(g, bufA0, 0);
    Sprintf_1343b8(bufA0, D_00461778, D_00461788, bufE0);
    sub->h10 = LoaderRequestFile_1cd870(g, bufA0, 0);
    strcpy(sub->name12, buf120);
    strcpy(sub->name32, bufE0);
    LoaderQueueAppendSeparator_1cd670(g);
    if (sub->hE < 0 || sub->h10 < 0) {
        LoaderReleaseById_1cd340(g, sub->hE);
        LoaderReleaseById_1cd340(g, sub->h10);
        EffectEntryReset_2dc550(&m->ents[slot]);
        r.type = 3;
        r.val = -1;
        r.z = 0;
        return r;
    }
    r.type = 3;
    r.val = v;
    r.z = 0;
    return r;
}
