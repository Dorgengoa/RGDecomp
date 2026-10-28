/* rgp:protos */
#define RGP_SELF_DListClear_42ea80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

typedef struct Node0042ea80 {
    struct Node0042ea80 *unk0;
    struct Node0042ea80 *unk4;
    s32 unk8;
} Node0042ea80;

typedef struct List0042ea80 {
    Node0042ea80 *unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
} List0042ea80;

void DListClear_42ea80(List0042ea80 *self)
{
    Node0042ea80 *node;
    Node0042ea80 *cur;
    Node0042ea80 *prev;
    Node0042ea80 *next;

    node = self->unk0;
    while ((cur = node) != NULL) {
        node = cur->unk4;
        prev = cur->unk0;
        if (prev != NULL) {
            prev->unk4 = cur->unk4;
        }
        next = cur->unk4;
        if (next != NULL) {
            next->unk0 = cur->unk0;
        }
        cur->unk8 = 0;
        cur->unk0 = NULL;
        cur->unk4 = NULL;
    }
    self->unk0 = NULL;
    self->unk4 = 0;
    self->unk8 = 0;
    self->unkA = 0;
}
