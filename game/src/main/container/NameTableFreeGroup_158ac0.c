/* rgp:protos */
#define RGP_SELF_NameTableFreeGroup_158ac0 1
#define RGP_SELF_getBucket 1
#define RGP_SELF_removeNode 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct N158 {
    s16 idx;
    u8 pad2[0x62];
    struct N158 *next;
} N158;

typedef struct B158 {
    s32 m0;
    s32 m4;
    N158 *head;
    s32 mC;
} B158;

typedef struct M158 {
    u8 pad0[8];
    s32 m8;
    s32 count;
    u8 pad10[0xC];
    B158 *buckets;
    B158 def;
    u8 pad30[0x1C8 - 0x30];
    N158 **freelist;
    u8 pad1cc[4];
    s32 nfree;
} M158;

/*rgp*/
/*rgp*/

static inline B158 *getBucket(M158 *m, s32 i)
{
    if (i == 0x7FFF) {
        return &m->def;
    }
    if (i < 0 || i >= m->count) {
        return NULL;
    }
    return &m->buckets[i];
}

static inline void removeNode(M158 *m, N158 *node)
{
    B158 *b;
    N158 *scan;
    N158 *prev;

    if (node == NULL) {
        return;
    }
    b = getBucket(m, node->idx);
    if (b == NULL) {
        return;
    }
    NameTableRemoveNode_15a0b0(m, node);
    prev = NULL;
    for (scan = b->head; scan != NULL; scan = scan->next) {
        if (scan == node) {
            if (prev == NULL) {
                b->head = scan->next;
            } else {
                prev->next = scan->next;
            }
        }
        prev = scan;
    }
    if (m->nfree > 0) {
        m->nfree--;
        m->freelist[m->nfree] = node;
    }
    NameTableNodeReset_15ada0(node);
}

void NameTableFreeGroup_158ac0(M158 *arg0, s32 arg1)
{
    B158 *b;
    N158 *node;
    N158 *next;

    b = getBucket(arg0, arg1);
    if (b == NULL) {
        return;
    }
    node = b->head;
    while (node != NULL) {
        next = node->next;
        removeNode(arg0, node);
        node = next;
    }
    b->m4 = 0;
    b->m0 = 0;
    b->mC = 0;
    b->head = NULL;
    arg0->m8 = -1;
}
