#include "types.h"
#pragma opt_lifetimes off

extern void NameTableRemoveNode_15a0b0(void *, void *);
extern void NameTableNodeReset_15ada0(void *);
extern void strcat(s8 *, s8 *);
extern s32 strcmp(s8 *, s8 *);
extern void strcpy(s8 *, s8 *);

typedef struct Ent158 {
    s16 id;
    u8 pad2[6];
    s8 name[0x5C];
    struct Ent158 *link;
} Ent158;

typedef struct Node158 {
    Ent158 *e;
    struct Node158 *next;
} Node158;

typedef struct {
    u8 pad0[8];
    Ent158 *head;
    u8 padC[4];
} Grp158;

typedef struct {
    u8 pad0[0xC];
    s32 ngrp;
    u8 pad10[0xC];
    Grp158 *grps;
    Grp158 def;
    Node158 *hash[101];
    u8 pad1c4[0x1C8 - 0x1C4];
    Ent158 **stack;
    u8 pad1cc[4];
    s32 sp;
    u8 pad1d4[0x10];
    s8 suffix[1];
} Obj158;

static inline Ent158 *find(Obj158 *o, s8 *name, s32 id, s8 *buf) {
    s8 *p;
    u8 h;
    Node158 *n;
    s32 c;
    Ent158 *r;

    if (name == NULL) {
        return NULL;
    }
    if (o->suffix[0] != 0) {
        strcpy(buf, name);
        strcat(buf, o->suffix);
        name = buf;
    }
    p = name;
    h = 0;
    while ((c = *p) != 0) {
        p++;
        h = ((h << 8) + c) % 101;
    }
    for (n = o->hash[h]; n != NULL; n = n->next) {
        if (strcmp(name, n->e->name) == 0) {
            if (id < 0 || n->e->id == id) {
                name = (s8 *)n->e;
            goto out;
            }
        }
    }
    name = NULL;
out:
    return (Ent158 *)name;
}

static inline Grp158 *grp(Obj158 *o, Ent158 *e) {
    s32 id;
    id = e->id;
    if (id == 0x7FFF) {
        return &o->def;
    }
    if (id < 0 || id >= o->ngrp) {
        return NULL;
    }
    return &o->grps[id];
}

static inline void rem(Obj158 *arg0, Ent158 *e) {
    Grp158 *g;
    Ent158 *cur;
    Ent158 *prev;
    s32 k;

    if (e == NULL) {
        return;
    }
    g = grp(arg0, e);
    if (g == NULL) {
        return;
    }
    NameTableRemoveNode_15a0b0(arg0, e);
    prev = NULL;
    for (cur = g->head; cur != NULL; cur = cur->link) {
        if (cur == e) {
            if (prev == NULL) {
                g->head = cur->link;
            } else {
                prev->link = cur->link;
            }
        }
        prev = cur;
    }
    k = arg0->sp;
    if (k > 0) {
        k = k - 1;
        arg0->sp = k;
        arg0->stack[k] = e;
    }
    NameTableNodeReset_15ada0(e);
}

void NameTableRemoveByName_158c40(Obj158 *arg0, s8 *arg1, s32 arg2)
{
    s8 sp50[0x80];
    Ent158 *e;

    e = find(arg0, arg1, arg2, sp50);
    if (e == NULL) {
        return;
    }
    rem(arg0, e);
}
