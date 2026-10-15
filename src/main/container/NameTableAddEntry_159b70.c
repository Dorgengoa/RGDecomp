#include "types.h"

typedef struct Ent {
    u8 pad0[6];
    s16 m6;
    u8 pad8[0x20];
    u16 m28;
    u8 pad2A[0xE];
    union {
        u64 d;
        struct {
            u64 x : 14;
            u64 p0 : 23;
            u64 y : 14;
            u64 p1 : 13;
        } b;
        struct {
            u16 x : 14;
            u16 f : 2;
        } h;
    } m38;
    u8 pad40[0x24];
    struct Ent *m64;
} Ent;

typedef struct Grp {
    u8 pad0[8];
    Ent *m8;
    u8 padC[4];
} Grp;

typedef struct Def {
    u8 pad0[8];
    char name[1];
} Def;

typedef struct Node {
    Def *def;
    struct Node *next;
} Node;

typedef struct Mgr {
    u8 pad0[4];
    s32 m4;
    u8 pad8[4];
    s32 mC;
    u8 pad10[0xC];
    Grp *m1C;
    Grp m20;
    Node *m30[101];
    u8 pad1C4[4];
    Ent **m1C8;
    s32 m1CC;
    s32 m1D0;
    u8 pad1D4[0x10];
    char m1E4[1];
} Mgr;

extern void NameTableLinkNode_15a180(Mgr *, Ent *);
extern s32 NameTableNodeSetImage_15a640(Ent *, s32, char *, s32, s32, s32, s32, s32, s64, s64);
extern char *strcat(char *, const char *);
extern s32 strcmp(const char *, const char *);
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char *, u32);
extern u8 D_00491888[0x400];
extern char D_00491889[0x400];

static __inline Grp *getGrp(Mgr *m, s32 i)
{
    if (i == 0x7FFF) {
        return &m->m20;
    }
    if (i < 0) {
        return NULL;
    }
    if (i < m->mC) {
        return &m->m1C[i];
    }
    return NULL;
}

static __inline Ent *alloc(Mgr *m)
{
    s32 n = m->m1D0;
    if (n < m->m1CC) {
        m->m1D0 = n + 1;
        return m->m1C8[n];
    }
    return NULL;
}

static __inline u8 hash(const char *p)
{
    u8 h = 0;
    while (*p != 0) {
        h = ((h << 8) + *p++) % 101;
    }
    return h;
}

static __inline s32 inRange(Mgr *m, s32 i)
{
    return i < m->mC;
}

static __inline Def *find(Mgr *m, const char *name)
{
    Node *n;
    for (n = m->m30[hash(name)]; n != NULL; n = n->next) {
        if (strcmp(name, n->def->name) == 0) {
            return n->def;
        }
    }
    return NULL;
}

static __inline Grp *getGrp2(Mgr *m, s32 i)
{
    Grp *g;
    if (i == 0x7FFF) {
        g = &m->m20;
    } else if (i < 0) {
        g = NULL;
    } else if (i < m->mC) {
        g = &m->m1C[i];
    } else {
        g = NULL;
    }
    return g;
}

static __inline Ent *alloc2(Mgr *m)
{
    Ent *e;
    s32 n = m->m1D0;
    if (n < m->m1CC) {
        m->m1D0 = n + 1;
        e = m->m1C8[n];
    } else {
        e = NULL;
    }
    return e;
}

Ent *NameTableAddEntry_159b70(Mgr *arg0, s32 arg1, char *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s64 arg8, s32 arg9)
{
    char name[0x40];
    char full[0x80];
    Grp *g;
    Ent *e;
    Ent *p;
    char *key;
    Def *d;
    s32 v;
    s32 ok;

    strcpy(name, arg2);
    strcat(name, arg0->m1E4);
    if (name[0] == 0) {
        return NULL;
    }
    if (arg1 == 0x7FFF) {
        g = &arg0->m20;
    } else if ((arg1 < 0) || (arg1 >= arg0->mC)) {
        g = NULL;
    } else {
        g = &arg0->m1C[arg1];
    }
    if (g == NULL) {
        return NULL;
    }
    v = arg0->m1D0;
    if (v >= arg0->m1CC) {
        e = NULL;
    } else {
        arg0->m1D0 = v + 1;
        e = arg0->m1C8[v];
    }
    key = name;
    if (arg0->m1E4[0] != 0) {
        strcpy(full, key);
        strcat(full, arg0->m1E4);
        key = full;
    }
    d = find(arg0, key);
    if (d != NULL) {
        D_00491888[0] = 1;
        strncpy(D_00491889, d->name, 0x20);
    }
    if (e == NULL) {
        return NULL;
    }
    if (NameTableNodeSetImage_15a640(e, arg1, name, arg3, arg4, arg5, arg6, arg7, arg8, arg9) == 0) {
        return NULL;
    }
    e->m64 = NULL;
    if (g->m8 == NULL) {
        g->m8 = e;
    } else {
        for (p = g->m8; p != NULL; p = p->m64) {
            if (p->m64 == NULL) {
                p->m64 = e;
                break;
            }
        }
    }
    NameTableLinkNode_15a180(arg0, e);
    if (arg1 == 0x7FFF) {
        v = arg0->m4;
        if (e->m6 < 9) {
            v -= 4;
            e->m38.b.y = v;
        }
        v -= e->m28;
        e->m38.h.x = v;
        arg0->m4 = v;
    }
    return e;
}
