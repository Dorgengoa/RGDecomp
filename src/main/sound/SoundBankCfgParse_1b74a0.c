#include "types.h"

typedef struct Ent {
    char *str;  /* 0x0 */
    s16 f4;     /* 0x4 */
    s8 f6;      /* 0x6 */
    s8 f7;      /* 0x7 */
    s8 f8;      /* 0x8 */
    s8 f9;      /* 0x9 */
    s8 fA;      /* 0xA */
    s8 fB;      /* 0xB */
} Ent;

typedef struct Tbl {
    u8 pad[0x18];
    s32 count;  /* 0x18 */
    Ent *ents;  /* 0x1C */
    u8 pad20[0x18];
} Tbl;

typedef struct Base {
    u8 pad[0x18];
    Tbl tbl[5];
} Base;

s32 ConstructNewArray_100710(void *, void *, s32, s32, s32);
void *MemStackAllocQw_14d950(s32, s32);
void *MemStackNew_14e1b0(s32, s32);
u32 TextSplitFields_1b78d0(char **, u32, u32);
s8 SoundBankCfgLookupKeyMaybe_1b7a80(Tbl *, char *, s32 *, s32 *);
s32 atoi(const char *);
void *memset(void *, s32, u32);
char *strcat(char *, const char *);
s32 strcmp(const char *, const char *);
char *strcpy(char *, const char *);
s32 strlen(const char *);
extern char D_0045AB80[];
extern char D_0045ABA8[];
extern char D_0045ABB0[];
extern char D_0045ABB8[];
extern char D_0045ABC0[];
extern char D_0045ABC8[];
extern s32 D_0048145C;
void SoundBankCfgEntryCtor_1b78b0(void);

static inline Tbl *GetTbl(Base *b, s32 n) {
    if (n < 0 || n >= 5) {
        return 0;
    }
    return &b->tbl[n];
}

void SoundBankCfgParse_1b74a0(Base *base, s32 n, u32 cur, u32 len, s32 heap) {
    s32 i21C;
    s32 i218;
    char b210[8];
    char b208[8];
    char b200[8];
    char b1F8[8];
    char b1B0[0x48];
    char b170[0x40];
    s8 b150[0x20];
    char b110[0x40];
    char bB0[0x60];
    Tbl *t;
    u32 end;
    u32 start;
    s32 i;
    s32 cnt;
    Ent *e;
    s8 v;
    char **pp;
    s32 l;
    s32 l1;
    char *s;

    t = GetTbl(base, n);
    if (t == 0) {
        return;
    }
    {
        char *ptrs[10] = {b210, b1B0, b170, (char *)b150, b110, b208, b200, b1F8, bB0};
    end = cur + len;
    start = cur;
    t->count = 0;
    while (cur < end) {
        cur = TextSplitFields_1b78d0(ptrs, cur, end);
        if (strcmp(ptrs[0], D_0045AB80) == 0) {
            break;
        }
        t->count++;
    }
    cnt = t->count;
    t->ents = (Ent *)ConstructNewArray_100710(MemStackNew_14e1b0(cnt * 12 + 16, heap), SoundBankCfgEntryCtor_1b78b0, 0, 12, cnt);
    if (t->ents == 0) {
        t->count = 0;
        return;
    }
    cur = start;
    i = 0;
    while (cur < end) {
        if (i >= t->count) {
            return;
        }
        for (pp = ptrs; *pp != 0; pp++) {
            **pp = 0;
        }
        cur = TextSplitFields_1b78d0(ptrs, cur, end);
        if (strcmp(ptrs[0], D_0045AB80) == 0) {
            return;
        }
        if (ptrs[0][0] < '0' || ptrs[0][0] >= ':') {
            continue;
        }
        e = &t->ents[i];
        i++;
        memset(e, 0, 12);
        e->f6 = SoundBankCfgLookupKeyMaybe_1b7a80(t, b110, &i21C, &i218);
        e->f9 = i218;
        e->f4 = atoi(b208);
        if (b150[0] && b150[0] != 0x2A) {
            if (strcmp((char *)b150, D_0045ABA8) == 0) {
                v = 9;
            } else if (strcmp((char *)b150, D_0045ABB0) == 0) {
                v = 3;
            } else if (strcmp((char *)b150, D_0045ABB8) == 0) {
                v = 4;
            } else if (strcmp((char *)b150, D_0045ABC0) == 0) {
                v = 6;
            } else if (strcmp((char *)b150, D_0045ABC8) == 0) {
                v = 8;
            } else {
                v = -1;
            }
            e->fA = v;
            if (v >= 0) {
                e->f6 = 4;
            }
        }
        if (e->f6 == 2) {
            e->f4 = i21C;
        }
        if (e->f6 == 3) {
            e->f4 = i21C;
        }
        e->f7 = atoi(b200);
        e->fB = b1F8[0] != 0;
        e->f8 = 0x40;
        if (D_0048145C != 0) {
            l = strlen(b1B0);
            l += strlen(bB0);
            if (l > 0) {
                s = MemStackAllocQw_14d950(heap, (l + 1) / 16 + 1);
                if (s != 0) {
                    strcpy(s, b1B0);
                    strcat(s, bB0);
                    e->str = s;
                }
            }
        }
    }
    }
}
