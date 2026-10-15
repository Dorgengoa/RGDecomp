#include "types.h"

typedef struct Entry {
    u8 data[0x80];
    s16 type;
    char name[0x82];
    struct Entry *next;
} Entry;

typedef struct Mgr {
    Entry *e;
    Entry *head;
} Mgr;

typedef struct Src {
    u8 pad00[0x40];
    s16 kind;
    s16 a;
    s16 b;
    u8 pad46[0xA];
    u8 x50[4];
} Src;

typedef struct Hdr {
    u8 pad00[0x22];
    s16 count;
} Hdr;

typedef struct Obj {
    u8 pad00[0x18];
    Hdr *hdr;
} Obj;

typedef struct Info {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    u8 pad10[0xC];
    void *p1C;
    void *p20;
    u8 pad24[0x8C];
} Info;

extern s32 Sprintf_1343b8(char *, void *);
extern void MsgFormat_28a9a0(void *, void *, Info *, s32);
extern void MsgFormatParamsCtor_28aa00(Info *);
extern void InsectCageMsgEntryReset_3848d0(Entry *, s32);
extern void *InsectCageMenuMsgLookup_389d30(s32);
extern void *InsectCageMenuGetInsectName_390e60(s32);
extern Src *InsectRecGetMsgEntry_3cee80(Obj *, s32);
extern void *memcpy(void *, const void *, u32);

extern u8 D_00463EB8[0x400];

static inline Entry *allocEntry(Mgr *m) {
    s32 j;
    for (j = 0; j < 64; j++) {
        if ((*(Entry (*)[64])m->e)[j].type < 0) {
            InsectCageMsgEntryReset_3848d0(&m->e[j], j);
            return &m->e[j];
        }
    }
    return 0;
}

s32 InsectCageMsgListBuild_3845b0(Mgr *mgr, Obj *obj, char *out) {
    Info info;
    s32 n;
    Entry *prev;
    s32 i;
    Src *src;
    Entry *e;

    if (obj == 0) {
        return 0;
    }
    if (out != 0) {
        *out = 0;
    }
    n = obj->hdr->count;
    if (n <= 0) {
        return 0;
    }
    prev = 0;
    for (i = 0; i < n; i++) {
        src = InsectRecGetMsgEntry_3cee80(obj, i);
        e = allocEntry(mgr);
        if (e == 0) {
            break;
        }
        memcpy(e, src, 0x80);
        MsgFormatParamsCtor_28aa00(&info);
        switch (src->kind) {
        case 1:
            e->type = 0x1389;
            info.p1C = InsectCageMenuGetInsectName_390e60(src->a);
            info.p20 = InsectCageMenuGetInsectName_390e60(src->b);
            break;
        case 2:
            e->type = 0x138A;
            info.p1C = src->x50;
            info.p20 = src->x50;
            break;
        case 3:
            e->type = 0x138B;
            info.p1C = InsectCageMenuGetInsectName_390e60(src->a);
            break;
        case 6:
            e->type = 0x138E;
            info.p1C = InsectCageMenuGetInsectName_390e60(src->a);
            break;
        case 4:
            e->type = 0x138C;
            info.p1C = InsectCageMenuGetInsectName_390e60(src->a);
            break;
        }
        MsgFormat_28a9a0(e->name, InsectCageMenuMsgLookup_389d30(e->type), &info, 1);
        if (prev != 0) {
            prev->next = e;
        }
        prev = e;
    }
    mgr->head = mgr->e;
    if (out != 0) {
        for (e = mgr->head; e != 0; e = e->next) {
            out += Sprintf_1343b8(out, InsectCageMenuMsgLookup_389d30(0x13F6));
            out += Sprintf_1343b8(out, e->name);
            if (e->next != 0) {
                out += Sprintf_1343b8(out, D_00463EB8);
            }
        }
    }
    return 1;
}
