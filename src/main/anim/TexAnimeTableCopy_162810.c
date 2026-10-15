#include "types.h"

typedef struct Col { u8 r, g, b, a; } Col;
typedef struct Ent {
    struct Ent *next;
    u8 pad4[0xC];
    s8 b10;
    s8 b11;
    s8 b12;
    s8 b13;
    s32 i14;
    s32 i18;
    s16 h1C;
    s16 h1E;
    s16 h20;
    s16 h22;
    s16 h24;
    s16 h26;
    s16 h28;
    s16 h2A;
    s16 h2C;
    s16 h2E;
    f32 f30;
    f32 f34;
    s16 h38;
    s16 h3A;
    s16 h3C;
    s16 h3E;
    s8 b40;
    s8 b41;
    s8 b42;
    u8 b43;
    Col c44;
} Ent;
typedef struct Tbl {
    s32 count;
    s32 a4[0x30];
    Ent *head[0x30];
    Ent *cur[0x30];
    s32 a244[0x30];
    s32 a304[0x30];
} Tbl;

extern Ent *TexAnimSeqNewKey_162d00(Tbl *, s32, s32);

static inline void Reset(Tbl *d, s32 i) {
    if (i >= 0 && i < d->count) {
        d->a4[i] = 0;
        d->cur[i] = d->head[i];
        d->a304[i] = 0;
    }
}

static inline void Clear(Tbl *d, s32 i) {
    if (i >= 0 && i < d->count) {
        Reset(d, i);
        d->head[i] = 0;
        d->cur[i] = 0;
        d->a244[i] = 0;
        d->a304[i] = 0;
    }
}

void TexAnimeTableCopy_162810(Tbl *src, Tbl *d, s32 arg2) {
    s32 i;
    s32 j;
    Ent *e;
    Ent *n;

    d->count = 0x30;
    for (i = 0; i < 0x30; i++) {
        Clear(d, i);
    }
    d->count = src->count;
    for (j = 0; j < src->count; j++) {
        d->a4[j] = src->a4[j];
        d->a244[j] = src->a244[j];
        if (arg2 == 0) {
            d->head[j] = src->head[j];
            d->cur[j] = src->head[j];
        } else {
            for (e = src->head[j]; e != 0; e = e->next) {
                n = TexAnimSeqNewKey_162d00(d, j, arg2);
                if (n != 0) {
                    n->b10 = e->b10;
                    n->b11 = e->b11;
                    n->b12 = e->b12;
                    n->b13 = e->b13;
                    n->i14 = e->i14;
                    n->i18 = e->i18;
                    n->h1C = e->h1C;
                    n->h1E = e->h1E;
                    n->h20 = e->h20;
                    n->h22 = e->h22;
                    n->h24 = e->h24;
                    n->h26 = e->h26;
                    n->h28 = e->h28;
                    n->h2A = e->h2A;
                    n->h2C = e->h2C;
                    n->h2E = e->h2E;
                    n->f30 = e->f30;
                    n->f34 = e->f34;
                    n->h38 = e->h38;
                    n->h3A = e->h3A;
                    n->h3C = e->h3C;
                    n->h3E = e->h3E;
                    n->b40 = e->b40;
                    n->b41 = e->b41;
                    n->b42 = e->b42;
                    n->b43 = e->b43;
                    n->c44 = e->c44;
                }
            }
            d->cur[(u32)j] = d->head[(u32)j];
        }
        d->a304[j] = 0;
    }
}
