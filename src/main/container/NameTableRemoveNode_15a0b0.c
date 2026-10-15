#include "types.h"

typedef struct Node15a { s32 key; struct Node15a *next; } Node15a;
typedef struct {
    u8 pad0[0x30];
    Node15a *bucket[101];
    u8 pad1C4[0x1D8 - 0x1C4];
    Node15a **free;
    s32 pad1DC;
    s32 nfree;
} Tbl15a;

void NameTableRemoveNode_15a0b0(Tbl15a *arg0, s32 arg1) {
    Node15a *cur;
    Node15a **pp;
    Node15a *prev;
    s8 *s;
    u8 h;
    Node15a *found;

    if (arg1 == 0) {
        return;
    }
    s = (s8 *)(arg1 + 8);
    h = 0;
    while (*s != 0) {
        h = ((h << 8) + *s++) % 101;
    }
    prev = 0;
    found = 0;
    pp = (Node15a **)((u8 *)(h * 4) + (s32)arg0 + 0x30);
    for (cur = *pp; cur != 0; cur = cur->next) {
        if (cur->key == arg1) {
            found = cur;
            break;
        }
        prev = cur;
    }
    if (found == 0) {
        return;
    }
    if (prev == 0) {
        *pp = found->next;
    } else {
        prev->next = found->next;
    }
    if (arg0->nfree > 0) {
        arg0->nfree--;
        arg0->free[arg0->nfree] = found;
    }
}
