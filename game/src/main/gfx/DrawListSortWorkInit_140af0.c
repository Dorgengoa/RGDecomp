/* rgp:protos */
#define RGP_SELF_DrawListSortWorkInit_140af0 1
#define RGP_SELF_QW 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct Info {
    u8 pad0[0xC];
    s32 n;
} Info;

typedef struct Self {
    u8 pad0[0x3BA0];
    Info *info;
    s8 *heap;
    s32 h;
    s32 flag;
    s32 *order;
    s32 n;
    s32 *map;
    s32 cnt;
    s32 *a;
    s32 *b;
    s32 *c;
    s32 *d;
    s32 dn;
    s32 dmax;
} Self;

/*rgp*/
/*rgp*/
/*rgp*/

static inline s32 QW(s32 n) {
    u32 b = n * 4;
    u32 q;
    if (b & 0xF) {
        q = (b >> 4) + 1;
    } else {
        q = b >> 4;
    }
    return q;
}

void DrawListSortWorkInit_140af0(Self *self, s8 *heap, s32 *list, s32 count) {
    Info *info;
    s8 *h;
    s32 nq;
    s32 i;
    s32 n;
    s32 *p;
    s32 *q;
    s32 *t;
    s32 r;
    s32 j;

    info = self->info;
    self->heap = NULL;
    if (heap == NULL || info == NULL) {
        return;
    }
    r = ((s32)MemStackHeapAlloc_14db10(heap, 2, 0, 0x40));
    self->h = r;
    if (r == 0) {
        return;
    }
    self->heap = heap;
    LightStateResetEmit_142b70(self);
    h = self->heap;
    self->cnt = self->n = info->n;
    self->order = NULL;
    self->map = NULL;
    nq = ((u32)(self->cnt * 4) >> 4) + 1;
    if (list != NULL) {
        self->map = MemStackAllocQw_14d950(h, QW(self->n));
        for (i = 0; i < self->n; i++) {
            self->map[i] = -1;
        }
        for (p = list, n = 0; *p >= 0; n++, p++) {
        }
        self->order = MemStackAllocQw_14d950(h, QW(n + 1));
        for (i = 0; i < n; i++) {
            self->order[i] = list[i];
            self->map[self->order[i]] = i;
        }
        self->order[i] = -1;
        nq = ((u32)(n * 4) >> 4) + 1;
        self->cnt = n;
    }
    self->a = MemStackAllocQw_14d950(h, nq);
    self->b = MemStackAllocQw_14d950(h, nq);
    self->c = MemStackAllocQw_14d950(h, nq);
    self->dn = count;
    self->dmax = count - 1;
    self->d = p = MemStackAllocQw_14d950(h, QW(self->dn));
    q = self->a;
    t = self->c;
    for (j = 0; j < self->cnt; j++) {
        *q++ = 0;
        *t++ = 0;
    }
    for (j = 0; j < self->dn; j++) {
        *p++ = 0;
    }
    self->flag = 0;
}
