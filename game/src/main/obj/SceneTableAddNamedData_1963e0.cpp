#include "types.h"
#pragma opt_propagation off
#undef NULL
#define NULL 0

struct Blk { u32 w[0x20]; };

struct Ent {
    char *name;
    Blk *data;
};

struct Tbl {
    u8 pad0[0x210];
    s32 n;
    Ent e[1];
};

extern "C" {
s32 MemStackAllocQw_14d950(s32 arg0, u32 arg1);
void *MemStackNew_14e230(s32 arg0, s32 arg1);
s32 strcmp(const char *a, const char *b);
char *strcpy(char *dst, const char *src);
u32 strlen(const char *s);
}

static inline bool isEmpty(Ent *e) { bool b; b = !(e->name != NULL); return b; }

static inline Ent *find(Tbl *t, char *name)
{
    s32 i;
    Ent *e;
    for (i = 0; i < t->n; i++) {
        e = &t->e[i];
        if (isEmpty(e)) {
            continue;
        }
        if (e->name != NULL && strcmp(e->name, name) == 0) {
            return e;
        }
    }
    return NULL;
}

extern "C" s32 SceneTableAddNamedData_1963e0(Tbl *t, char *name, Blk *src, s32 heap)
{
    Ent *hit;
    Ent *slot;
    s32 i;
    u32 len;
    Blk *d;

    if (name == NULL) {
        return 0;
    }
    hit = find(t, name);
    if (hit != NULL) {
        return 0;
    }
    slot = NULL;
    for (i = 0; i < t->n; i++) {
        if (isEmpty(&t->e[i])) {
            slot = &t->e[i];
        }
    }
    if (slot == NULL) {
        return 0;
    }
    if (name != NULL) {
    slot->name = NULL;
    len = strlen(name) + 1;
    slot->name = (char *)MemStackAllocQw_14d950(heap, (len & 0xF) != 0 ? (len >> 4) + 1 : len >> 4);
    strcpy(slot->name, name);
    slot->data = NULL;
    if (src != NULL) {
        slot->data = (Blk *)MemStackNew_14e230(0x100, heap);
        d = slot->data;
        d[0] = src[0];
        d[1] = src[1];
    }
    }
    return 1;
}
