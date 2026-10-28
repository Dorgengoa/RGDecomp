#pragma opt_propagation off
#include "types.h"

typedef struct Node42 {
    struct Node42 *prev;
    struct Node42 *next;
    struct List42 *list;
    s32 unkC;
} Node42;

typedef struct List42 {
    Node42 *head;
    Node42 *tail;
    u16 count;
    u16 cap;
} List42;

static inline bool valid42(void *p) { return p != 0; }

extern "C" void DListNodeDetach_42eb50(Node42 *arg0) {
    List42 *l;
    u16 v;
    bool ok;

    l = arg0->list;
    if (l != 0) {
    ok = arg0 != 0;
    if (ok) {
        if (l->head == arg0) {
            l->head = arg0->next;
        }
        if (l->tail == arg0) {
            l->tail = arg0->prev;
        }
        if (arg0->prev != 0) {
            arg0->prev->next = arg0->next;
        }
        if (arg0->next != 0) {
            arg0->next->prev = arg0->prev;
        }
        arg0->list = 0;
        arg0->prev = 0;
        arg0->next = 0;
        l->count--;
        for (l->cap = 1; l->cap < l->count; ) {
            l->cap = *(volatile u16 *)&l->cap * 2;
        }
    }
    }
    arg0->prev = 0;
    arg0->next = 0;
    arg0->list = 0;
    arg0->unkC = 0;
}
