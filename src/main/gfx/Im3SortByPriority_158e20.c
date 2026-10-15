#include "types.h"


typedef struct {
    u8 type;
    u8 pad1[0x2B];
    s32 prio;
    u8 pad30[0x10];
} Ent;

typedef struct {
    u8 magic[4];
    s32 ofs;
    u32 count;
} Hdr;

s32 memcmp(const void *, const void *, u32);
void *memcpy(void *, const void *, u32);
extern u8 D_00458B18[];



static inline u8 IsSkip(Ent *e) {
    return e->type == 0x23;
}

void Im3SortByPriority_158e20(Hdr *arg0) {
    Ent tmp;
    Ent *base;
    u32 i;
    u32 j;
    Ent *a;
    Ent *b;
    s32 *p;

    if (memcmp(arg0, D_00458B18, 3) != 0) {
        return;
    }
    base = (Ent *)((u8 *)arg0 + arg0->ofs);
    for (i = 0; i < arg0->count - 1; i++) {
        a = &base[i];
        for (j = i + 1; j < arg0->count; j++) {
            if (a->prio < 0) {
                a->prio = 0;
            }
            b = &base[j];
            p = &b->prio;
            if (*p < 0) {
                *p = 0;
            }
            if (a->prio > *p && !IsSkip(b)) {
                memcpy(&tmp, a, 0x40);
                memcpy(a, (Ent *)((u8 *)base + (j << 6)), 0x40);
                memcpy((Ent *)((u8 *)base + (j << 6)), &tmp, 0x40);
            }
        }
    }
}
