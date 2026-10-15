/* PARKED s17b: not attempted. Nested double loop over a 2-level array
   (arg0->unk4, stride 0x14, inner elements stride 0x24) doing a hash-table
   insert-or-find (linked list via ->unk0/->unk4/->unk10) keyed by a string
   compare, allocating a new 0x1C-byte node via MemStackNew_14e230 on miss. Needs a
   careful asm read of asm/matchings/main/AmixerBindResByNameMaybe_170330.s to pin down the
   struct strides before drafting. Not attempted this lane. */
/* s49m: len(ed=15,d=-6) */
#include "types.h"
#undef NULL
#define NULL 0

class Node {
public:
    Node *next;
    Node *prev;
    s32 pad8;
    s32 padC;
    char *key;
    s32 m;
    virtual void init();
};

typedef struct Elem {
    s32 pad0;
    char *name;
    s32 *ref;
    u8 padC[0x18];
} Elem;

typedef struct Group {
    s32 count;
    Elem *items;
    u8 pad8[0xC];
} Group;

typedef struct Owner {
    s32 count;
    Group *groups;
    s32 pad8;
    s32 padC;
    Node *head;
} Owner;

extern "C" {
extern s32 ArchiveGetFileData_181dd0(s32, char *, s32 *);
extern s32 strcmp(const char *, const char *);
extern Node *MemStackNew_14e230(s32, s32);
extern void MotResHandleCtorMaybe_154700(s32 *);
extern char *MemStackStrDup_14cf10(char *, s32);
extern void MotResCopyAndRelocate_154650(s32 *, s32, s32, s32);
extern u8 D_00470310[];
}

static inline Node *find(Owner *o, char *name)
{
    Node *n;

    if (name == NULL) {
        return NULL;
    }
    for (n = o->head; n != NULL; n = n->next) {
        if (n->key != NULL && strcmp(n->key, name) == 0) {
            return n;
        }
    }
    return NULL;
}

extern "C" s32 AmixerBindResByNameMaybe_170330(Owner *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 spBC;
    Group *g;
    s32 n;
    Elem *e;
    s32 i, j;
    s32 cnt;
    s32 r;
    Node *nd;
    Node *p;
    char **obj;

    g = arg0->groups;
    if (g == NULL) {
        return 0;
    }
    n = 0;
    for (i = 0; i < arg0->count; i++, g++) {
        e = g->items;
        cnt = g->count;
        for (j = 0; j < cnt; j++, e++) {
            r = ArchiveGetFileData_181dd0(arg1, e->name, &spBC);
            nd = find(arg0, e->name);
            obj = nd == NULL ? NULL : &nd->key;
            if (obj == NULL) {
                nd = MemStackNew_14e230(0x1C, arg2);
                if (nd != NULL) {
                    *(u8 **)((u8 *)nd + 0x18) = D_00470310;
                    MotResHandleCtorMaybe_154700(&nd->m);
                    nd->key = NULL;
                    nd->init();
                }
                if (nd == NULL) {
                    obj = NULL;
                } else {
                    if (arg0->head == NULL) {
                        arg0->head = nd;
                    } else {
                        p = arg0->head;
                        while (p != NULL) {
                            if (p->next == NULL) {
                                break;
                            }
                            p = p->next;
                        }
                        p->next = nd;
                        if (nd != NULL) {
                            nd->prev = p;
                        }
                    }
                    obj = &nd->key;
                }
                if (obj != NULL) {
                    *obj = MemStackStrDup_14cf10(e->name, arg2);
                    if (arg3 == 0) {
                        spBC = 0;
                    }
                    MotResCopyAndRelocate_154650((s32 *)(obj + 1), r, arg2, spBC);
                }
            }
            if (obj != NULL) {
                n++;
                e->ref = (s32 *)(obj + 1);
            }
        }
    }
    return n;
}
