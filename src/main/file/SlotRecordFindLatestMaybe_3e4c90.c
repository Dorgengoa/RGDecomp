#include "types.h"

typedef struct Tbl {
    s16 n;
    s16 pad2;
    u8 *arr;
} Tbl;

typedef struct Self {
    u8 pad0[0x68];
    Tbl *tbl;
} Self;

u32 SlotRecordFindLatestMaybe_3e4c90(Self *self, s32 *out)
{
    Tbl *tbl;
    u32 best;
    s32 i;
    s32 n;
    u8 *e;

    tbl = self->tbl;
    if (tbl == NULL) {
        return 0;
    }
    if (tbl->arr == NULL) {
        return 0;
    }
    n = tbl->n;
    best = 0;
    if (out != NULL) {
        *out = 0;
    }
    for (i = 0; i < n; i++) {
        e = self->tbl->arr;
        e += i * 0x350;
        if (best < *(u32 *)(e + 8)) {
            best = *(u32 *)(e + 8);
            if (out != NULL) {
                *out = *(s16 *)(e + 2);
            }
        }
    }
    return best;
}
