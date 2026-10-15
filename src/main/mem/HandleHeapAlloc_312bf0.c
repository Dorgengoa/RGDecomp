#pragma divbyzerocheck on
#include "types.h"

typedef struct Hdr {
    u8 *ptr;
    s32 used;
    struct Hdr *next;
} Hdr;

typedef struct {
    u8 pad0[8];
    u32 bs;
    u8 *base;
    u8 *top;
    Hdr *head;
    Hdr *tail;
    Hdr *free;
    u32 hsize;
} Pool;

extern void HandleHeapCompact_312aa0(Pool *);

static inline Hdr *newHdr(Pool *p)
{
    Hdr *h;
    u8 *top;
    u32 hs;

    h = p->free;
    if (h != NULL) {
        p->free = h->next;
    } else {
        hs = p->hsize;
        top = p->top;
        if ((u32)(top - p->base) < hs) {
            return NULL;
        }
        h = (Hdr *)(top - hs);
        p->top = (u8 *)h;
    }
    h->next = NULL;
    h->ptr = NULL;
    return h;
}

void HandleHeapAlloc_312bf0(Hdr **out, Pool *p, u32 size)
{
    u32 n;
    Hdr *h;
    u8 retried;
    u8 *b;

    n = p->bs * ((size + p->bs - 1) / p->bs);
    if (n == 0) {
        n = p->bs;
    }
    retried = 0;
    h = newHdr(p);
    if (h == NULL) {
        HandleHeapCompact_312aa0(p);
        h = newHdr(p);
        retried = 1;
    }
    if (h == NULL) {
        *out = NULL;
        return;
    }
    if ((u32)(p->top - p->base) < n) {
        if (!retried) {
            HandleHeapCompact_312aa0(p);
        } else {
            h->next = p->free;
            p->free = h;
            *out = NULL;
            return;
        }
    }
    if ((u32)(p->top - p->base) < n) {
        h->next = p->free;
        p->free = h;
        *out = NULL;
        return;
    }
    b = p->base;
    p->base = b + n;
    h->ptr = b;
    h->used = 1;
    if (p->head == NULL) {
        p->head = h;
    } else {
        p->tail->next = h;
    }
    p->tail = h;
    *out = h;
}
