#include "types.h"

struct Rec {
    u8 pad0[0x12];
    s16 key;
    u8 pad14[0x10];
    s32 f24;
    s32 f28;
    u8 pad2c[0x10];
};

struct SortEntry {
    s16 key;
    s16 pad;
    Rec *ptr;
};

struct Obj {
    u8 pad0[0x10];
    s32 f10;
    u8 pad14[0x68];
    s16 f7C;
    u8 pad7e[0xE];
    Rec *f8C;
    u8 pad90[0x10];
    s16 fA0;
    s16 padA2;
    SortEntry *fA4;
};

extern "C" void *MemStackNew_14e0b0(s32, s32);
extern "C" void *memcpy(void *, const void *, u32);

extern "C" s32 DataTableBuildSortedIndex_403720(Obj *o)
{
    SortEntry tmp __attribute__((aligned(16)));
    bool swapped;
    s32 j;
    SortEntry *e;
    bool sw;
    Rec *b;
    SortEntry *prev;
    Rec *r;
    Rec *a;
    s32 k;
    SortEntry *cur;
    s32 i;

    if (o->f10 == 0) {
        return 0;
    }
    if (o->f8C == 0) {
        return 0;
    }
    if (o->f7C <= 0 || o->fA0 <= 0) {
        o->fA0 = 0;
        o->fA4 = 0;
        return 1;
    }
    {
        e = (SortEntry *)MemStackNew_14e0b0(o->fA0 * 8, o->f10);
        o->fA4 = e;
        if (e == 0) {
            return 0;
        }
        r = o->f8C;
        for (j = 0, i = 0; i < o->f7C; i++, j++) {
            if (j >= o->fA0) break;
            e->key = r->key;
            e->ptr = r;
            r++;
            e++;
        }
        do {
            prev = o->fA4;
            swapped = false;
            for (k = 1; k < o->fA0; k++) {
                cur = &o->fA4[k];
                sw = false;
                if (prev->key > cur->key) {
                    sw = true;
                } else if (prev->key == cur->key) {
                    a = prev->ptr;
                    if (a == 0 && cur->ptr != 0) {
                        sw = true;
                    } else if (a != 0 && (b = cur->ptr) != 0) {
                        if (a->f24 == 0 && b->f24 != 0) {
                            sw = true;
                        } else if (a->f24 != 0 && b->f24 != 0 && a->f28 == 0 && b->f28 != 0) {
                            sw = true;
                        }
                    }
                }
                if (sw) {
                    memcpy(&tmp, cur, 8);
                    memcpy(cur, prev, 8);
                    memcpy(prev, &tmp, 8);
                    swapped = true;
                }
                prev = cur;
            }
        } while (swapped);
    }
    return 1;
}
