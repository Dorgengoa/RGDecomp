/* rgp:protos */
#define RGP_SELF_BuildKeywordHashTable_15f270 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_dead_code off
typedef struct Ent {
    s8 *name;
    s32 x4;
} Ent;

typedef struct Node {
    struct Node *next;
    s8 *name;
    s32 idx;
    s32 xC;
} Node;

typedef struct Self {
    u8 pad0[0x28];
    s32 count;
    Ent *ents;
    u8 pad30[4];
    Node **table;
    u8 pad38[8];
    Node *buckets[0x68];
    Node nodes[1];
} Self;

/*rgp*/

void BuildKeywordHashTable_15f270(Self *self, Ent *arg1)
{
    Ent *e;
    Node *node;
    Ent *e2;
    Node *cur;
    Node **slot;
    Node *p;
    Node *nx;
    s32 i;

    self->ents = arg1;
    self->count = 0;
    e = self->ents;
    self->count = 0;
    while (e->name && *e->name) {
        e++;
        self->count++;
    }
    self->table = NULL;
    if (self->count >= 0x80) {
        return;
    }
    self->table = (Node **)((u8 *)self + 0x40);
    node = (Node *)((u8 *)self->table + 0x1A0);
    for (i = 0; i < 0x65; i++) {
        self->table[i] = NULL;
    }
    e2 = self->ents;
    for (i = 0; i < self->count; i++, e2++) {
        node->next = NULL;
        cur = node;
        node++;
        cur->name = e2->name;
        cur->idx = i;
        { s32 h_ = StrHash101_15f3b0(self, e2->name); slot = (Node **)((u32)*(Node ** volatile *)&self->table + h_ * 4); }
        p = *slot;
        if (p == NULL) {
            *slot = cur;
        } else {
            while (p != NULL) {
                nx = *(void **)p;
                if (nx == NULL) {
                    *(void **)p = cur;
                    break;
                }
                p = nx;
            }
        }
    }
}
