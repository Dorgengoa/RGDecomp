#include "types.h"
#pragma optimization_level 3

typedef struct Entry { s16 key; s16 val; } Entry;
typedef struct Tbl { u8 pad[0x9C]; s16 count; s16 pad9E; Entry *data; } Tbl;

static inline s32 Cmp(s32 key, Entry *e) {
    if (e->key == key) return 0;
    if (key < e->key) return -1;
    return 1;
}
static inline s32 Cmp2(s32 key, Entry *e) {
    if (e->key == key) return 0;
    if (e->key < key) return 1;
    return -1;
}

Entry *DataTableSortedIndexFindRange_413cb0(Tbl *t, s32 key, s32 *count) {
    Entry *found;
    s32 lo;
    s32 hi;
    s32 mid;
    s32 c;
    Entry *last;
    Entry *p;
    Entry *pm;

    if (t->data == 0 || t->count <= 0) return 0;
    *count = 0;
    found = 0;
    hi = t->count - 1;
    lo = 0;
    c = Cmp(key, &t->data[0]);
    if (c == 0) {
        found = t->data;
    } else {
        if (c < 0) return 0;
        lo++;
        if (hi < lo) return 0;
    }
    if (found == 0) {
        c = Cmp2(key, &t->data[hi]);
        if (c == 0) {
            found = &t->data[hi];
        } else {
            if (c > 0) return 0;
            hi--;
            if (hi < lo) return 0;
        }
    }
    if (found == 0) {
        while (lo <= hi) {
            mid = lo + (hi - lo + 1) / 2;
            pm = &t->data[mid];
            c = Cmp2(key, pm);
            if (c == 0) {
                found = pm;
                break;
            }
            if (c > 0) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    if (found != 0) {
        while (found > t->data) {
            p = found - 1;
            if (p->key != key) break;
            found = p;
        }
    }
    if (found != 0) {
        *count = 1;
        last = t->data + t->count - 1;
        if (found < last) {
            p = found + 1;
            while (p <= last) {
                if (p->key != key) break;
                p++;
                (*count)++;
            }
        }
    }
    return found;
}
