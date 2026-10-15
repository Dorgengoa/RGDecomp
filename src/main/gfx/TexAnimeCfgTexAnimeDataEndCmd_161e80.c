#include "types.h"

typedef struct {
    s32 count;
    s32 a[0x30];
    s32 b[0x30];
    s32 c[0x30];
    s32 d[0x30];
    s32 e[0x30];
} Table;

extern Table *MemStackNew_14e230(s32, s32);
extern void *TableGetEntryOrDefault_159f60(s32, s32);
extern void TexAnimSeqAddKey_162b70(Table *, void *, s32);
extern Table *D_0048112C;
extern Table *D_00481130;
extern s32 D_00481134;
extern s32 D_00481138;
extern s32 D_0048113C;
extern s32 D_00481140;
extern s32 D_00481144;
extern s32 D_00481148;
extern u8 D_00495E70[];
extern s8 D_00495E71[];
extern s32 D_00495E74[];
extern s32 D_00495E78[];

static inline void reset(Table *t, s32 i) {
    if (i >= 0 && i < t->count) {
        t->a[i] = 0;
        t->c[i] = t->b[i];
        t->e[i] = 0;
    }
}

static inline void clear(Table *t, s32 i) {
    if (i >= 0 && i < t->count) {
        reset(t, i);
        t->b[i] = 0;
        t->c[i] = 0;
        t->d[i] = 0;
        t->e[i] = 0;
    }
}

static inline s32 find(Table *t) {
    s32 i;
    for (i = 0; i < t->count; i++) {
        if (t->b[i] == 0) {
            return i;
        }
    }
    return -1;
}

static inline void setd(Table *t, s32 i, s32 v) {
    if (i >= 0 && i < t->count) {
        t->d[i] = v;
    }
}

static inline void seta(Table *t, s32 i) {
    if (i >= 0 && i < t->count) {
        t->a[i] = 1;
    }
}

s32 TexAnimeCfgTexAnimeDataEndCmd_161e80(void) {
    void *obj;
    Table *t;
    Table *n;
    s32 i;

    if (D_00481148 < 0) {
        return 0;
    }
    obj = TableGetEntryOrDefault_159f60(D_00481138, D_00481148);
    if (obj == 0) {
        return 0;
    }
    if (D_00481130 != 0) {
        D_0048112C = D_00481130;
    } else {
        D_0048112C = *(Table **)((u8 *)obj + 0xC);
    }
    t = *(Table *volatile *)&D_0048112C;
    if (t == 0) {
        if (D_00481130 == 0) {
            n = MemStackNew_14e230(0x3C4, D_0048113C);
            if (n != 0) {
                n->count = 0x30;
                for (i = 0; i < 0x30; i++) {
                    clear(n, i);
                }
            }
            *(Table **)((u8 *)obj + 0xC) = n;
            D_0048112C = n;
        } else {
            D_0048112C = D_00481130;
        }
        t = *(Table *volatile *)&D_0048112C;
        if (t != 0) {
            D_00481134 = find(t);
        }
    } else if (D_00481134 < 0) {
        D_00481134 = find(t);
    }
    if (t != 0 && D_00481134 >= 0) {
        i = D_00481134;
        D_00495E71[0] = i;
        setd(t, i, D_00481140);
        if (D_00481144 != 0) {
            seta(D_0048112C, D_00481134);
        } else {
            reset(D_0048112C, D_00481134);
        }
        if (D_00495E74[0] != 0 && D_00495E78[0] != 0) {
            TexAnimSeqAddKey_162b70(D_0048112C, D_00495E70, D_0048113C);
        }
    }
    return 1;
}
