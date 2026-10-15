#include "types.h"

class Node {
public:
    Node *next;
    Node *prev;
    s32 m8;
    s32 mC;
    s32 m10;
    virtual void init();
};

typedef struct {
    char *name;
    s32 m4;
    s32 m8;
    Node *list;
} Ent;

typedef struct {
    u8 pad0[0x2A8];
    s32 n;
    Ent e[1];
} Tbl;

extern "C" {
extern s32 MemStackStrDup_14cff0(char *, s32);
extern Node *MemStackNew_14e230(s32, s32);
extern s32 strcmp(const char *, const char *);
extern u8 D_00470508[];
}

static inline u8 isnull(char *p) { return (p != 0) ^ 1; }

extern "C" s32 MapPartsGroupAdd_189c00(Tbl *t, char *name, s32 val, s32 heap)
{
    s32 i;
    s32 id;
    s32 j;
    Ent *ent;
    Node *p;
    Node *n;

    for (i = 0; i < t->n; i++) {
        if (isnull(t->e[i].name)) {
            continue;
        }
        if (strcmp(t->e[i].name, name) == 0) {
            id = 0;
            goto found;
        }
    }
    i = -1;
    id = 0;
found:
    if (i < 0) {
        for (j = 0; j < t->n; j++) {
            if (isnull(t->e[j].name)) {
                i = j;
                goto empty;
            }
        }
        i = -1;
    empty:
        id = MemStackStrDup_14cff0(name, heap);
    }
    if (i < 0 || i >= t->n) {
        ent = 0;
    } else {
        ent = &t->e[i];
    }
    if (ent == 0) {
        return -1;
    }
    if (id != 0) {
        *(s32 *)ent = id;
    }
    n = MemStackNew_14e230(0x18, heap);
    if (n != 0) {
        *(u8 **)((u8 *)n + 0x14) = D_00470508;
        n->m10 = 0;
        n->init();
    }
    n->m10 = val;
    if (ent->list == 0) {
        ent->list = n;
    } else {
        p = ent->list;
        while (p != 0) {
            if (p->next == 0) {
                break;
            }
            p = p->next;
        }
        p->next = n;
        if (n != 0) {
            n->prev = p;
        }
    }
    return i;
}
